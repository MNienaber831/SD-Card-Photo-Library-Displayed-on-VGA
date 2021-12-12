#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include "Altera_UP_SD_Card_Avalon_Interface.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

#define MAX_IMGS 5

/********************************************************************************
 * This program demonstrates use of the Altera University Program SD Card drivers,
 * pixel buffer HAL code, and pushbutton interrupts.
 * It:
 * 	-- Accesses SD card data with Altera UP SD Card drivers
 *		-- Reads the SD card .bmp images
 *	-- Displays the .bmp images using pixel buffer HAL code
 *	-- Scrolls through the .bmp images using pushbutton interrupts
********************************************************************************/
alt_up_pixel_buffer_dma_dev *pixel_buffer_dev;
alt_up_sd_card_dev * sd_card;
volatile int i, j;
volatile int edge_capture;
short int attributes;
short int handler;
short att1=0, att2=0, att3=0, att;
short buffer[512][256];
char *imgnames[MAX_IMGS] = {"img0.bmp", "img1.bmp", "img2.bmp", "img3.bmp", "img4.bmp"};
int count = 0;
int pixel;

void handle_key_interrupts(void* context);

static void pio_init();

void key3_isr();
void key2_isr();
void key1_isr();
void key0_isr();

int main(void)
{
	pio_init();

	sd_card = alt_up_sd_card_open_dev("/dev/SD_Card");

		if (sd_card!=NULL){
			if (alt_up_sd_card_is_Present()){
				printf("An SD Card was found!\n");
			}
			else {
				printf("No SD Card Found. \n Exiting the program.");
				return -1;
			}

			if (alt_up_sd_card_is_FAT16()){
				printf("FAT-16 partiton found!\n");

				handler = alt_up_sd_card_fopen(imgnames[count], false);
				att = alt_up_sd_card_get_attributes(handler);

				/* initialize the pixel buffer HAL */
				pixel_buffer_dev = alt_up_pixel_buffer_dma_open_dev ("/dev/VGA_Subsystem_VGA_Pixel_DMA");
				if ( pixel_buffer_dev == NULL)
					alt_printf ("Error: could not open VGA pixel buffer device\n");
				else
					alt_printf ("Opened character VGA pixel buffer device\n");

				/* set both the main buffer and back buffer to the allocated space */
				alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer_dev, (unsigned int) buffer);
				alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer_dev);
				while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer_dev));
					alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer_dev, (unsigned int) buffer);

				/* clear the graphics screen */
				alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 0);

				for (j = 0; j < 54; j++){										// Skip the header
					att1 = alt_up_sd_card_read(handler);
				}
				i = 0;
				j = 0;
				for (i = 240; i >= 0; i = i - 1){
					for(j = 0; j< 320; j = j + 1){
						att1 = (unsigned char)alt_up_sd_card_read(handler);		// Read each byte
						att2 = (unsigned char)alt_up_sd_card_read(handler);
						att3 = (unsigned char)alt_up_sd_card_read(handler);
						pixel = ((att3>>3)<<11) | ((att2>>2)<< 5) | (att1>>3);	// 24bit to 16-bit conversion
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, j, i, j, i, pixel, 0);
					}
				}
				alt_up_sd_card_fclose(handler);
			}
			else{
			printf("No FAT-16 partition found - Exiting!\n");
			return -1;
			}

		}

			while(1){

			}
}

void handle_key_interrupts(void* context) {
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);

	if(*edge_capture_ptr == 8) key3_isr();
	else if(*edge_capture_ptr == 4) key2_isr();
	else if(*edge_capture_ptr == 2) key1_isr();
	else if(*edge_capture_ptr == 1) key0_isr();
	return;
}

static void pio_init () {
	void* edge_capture_ptr = (void*) &edge_capture;
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSHBUTTONS_BASE,15);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE,0);
	alt_irq_register(PUSHBUTTONS_IRQ,edge_capture_ptr,handle_key_interrupts);
}

void key3_isr() {

	if (sd_card!=NULL){
		if (alt_up_sd_card_is_Present()){
			printf("An SD Card was found!\n");
		}
		else {
			printf("No SD Card Found. \n Exiting the program.");
			return;
		}

		if (alt_up_sd_card_is_FAT16()){
			printf("FAT-16 partiton found!\n");

			if(count == 0) {
				count = MAX_IMGS - 1;
				handler = alt_up_sd_card_fopen(imgnames[count], false);
			}
			else {
			handler = alt_up_sd_card_fopen(imgnames[--count], false);
			att = alt_up_sd_card_get_attributes(handler);
			}

			/* initialize the pixel buffer HAL */
			pixel_buffer_dev = alt_up_pixel_buffer_dma_open_dev ("/dev/VGA_Subsystem_VGA_Pixel_DMA");
			if ( pixel_buffer_dev == NULL)
				alt_printf ("Error: could not open VGA pixel buffer device\n");
			else
				alt_printf ("Opened character VGA pixel buffer device\n");

			/* clear the graphics screen */
			alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 0);

			for (j = 0; j < 54; j++){										// Skip the header
				att1 = alt_up_sd_card_read(handler);
			}
			i = 0;
			j = 0;
			for (i = 240; i >= 0; i = i - 1){
				for(j = 0; j< 320; j = j + 1){
					att1 = (unsigned char)alt_up_sd_card_read(handler);		// Read each byte
					att2 = (unsigned char)alt_up_sd_card_read(handler);
					att3 = (unsigned char)alt_up_sd_card_read(handler);
					pixel = ((att3>>3)<<11) | ((att2>>2)<< 5) | (att1>>3);	// 24bit to 16-bit conversion
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, j, i, j, i, pixel, 0);
				}
			}
			alt_up_sd_card_fclose(handler);
		}
		else{
			printf("No FAT-16 partition found - Exiting!\n");
			return;
		}


	}

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0x0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);

}

void key2_isr() {

	if (sd_card!=NULL){
		if (alt_up_sd_card_is_Present()){
			printf("An SD Card was found!\n");
		}
		else {
			printf("No SD Card Found. \n Exiting the program.");
			return;
		}

		if (alt_up_sd_card_is_FAT16()){
			printf("FAT-16 partiton found!\n");

			if(count == MAX_IMGS - 1) count = -1;
			handler = alt_up_sd_card_fopen(imgnames[++count], false);
			att = alt_up_sd_card_get_attributes(handler);

			/* initialize the pixel buffer HAL */
			pixel_buffer_dev = alt_up_pixel_buffer_dma_open_dev ("/dev/VGA_Subsystem_VGA_Pixel_DMA");
			if ( pixel_buffer_dev == NULL)
				alt_printf ("Error: could not open VGA pixel buffer device\n");
			else
				alt_printf ("Opened character VGA pixel buffer device\n");

			/* clear the graphics screen */
			alt_up_pixel_buffer_dma_clear_screen(pixel_buffer_dev, 0);

			for (j = 0; j < 54; j++){										// Skip the header
				att1 = alt_up_sd_card_read(handler);
			}
			i = 0;
			j = 0;
			for (i = 240; i >= 0; i = i - 1){
				for(j = 0; j< 320; j = j + 1){
					att1 = (unsigned char)alt_up_sd_card_read(handler);		// Read each byte
					att2 = (unsigned char)alt_up_sd_card_read(handler);
					att3 = (unsigned char)alt_up_sd_card_read(handler);
					pixel = ((att3>>3)<<11) | ((att2>>2)<< 5) | (att1>>3);	// 24bit to 16-bit conversion
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer_dev, j, i, j, i, pixel, 0);
				}
			}
		alt_up_sd_card_fclose(handler);

		}
		else{
		printf("No FAT-16 partition found - Exiting!\n");
		return;
		}

	}

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0x0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
}

void key1_isr() {

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0x0);
    IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);

}

void key0_isr() {

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 0x0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE);
}
