	nios_system u0 (
		.vga_CLK                    (<connected-to-vga_CLK>),                    //                  vga.CLK
		.vga_HS                     (<connected-to-vga_HS>),                     //                     .HS
		.vga_VS                     (<connected-to-vga_VS>),                     //                     .VS
		.vga_BLANK                  (<connected-to-vga_BLANK>),                  //                     .BLANK
		.vga_SYNC                   (<connected-to-vga_SYNC>),                   //                     .SYNC
		.vga_R                      (<connected-to-vga_R>),                      //                     .R
		.vga_G                      (<connected-to-vga_G>),                      //                     .G
		.vga_B                      (<connected-to-vga_B>),                      //                     .B
		.vga_pll_ref_clk_clk        (<connected-to-vga_pll_ref_clk_clk>),        //      vga_pll_ref_clk.clk
		.vga_pll_ref_reset_reset    (<connected-to-vga_pll_ref_reset_reset>),    //    vga_pll_ref_reset.reset
		.pushbuttons_export         (<connected-to-pushbuttons_export>),         //          pushbuttons.export
		.sd_card_b_SD_cmd           (<connected-to-sd_card_b_SD_cmd>),           //              sd_card.b_SD_cmd
		.sd_card_b_SD_dat           (<connected-to-sd_card_b_SD_dat>),           //                     .b_SD_dat
		.sd_card_b_SD_dat3          (<connected-to-sd_card_b_SD_dat3>),          //                     .b_SD_dat3
		.sd_card_o_SD_clock         (<connected-to-sd_card_o_SD_clock>),         //                     .o_SD_clock
		.sram_DQ                    (<connected-to-sram_DQ>),                    //                 sram.DQ
		.sram_ADDR                  (<connected-to-sram_ADDR>),                  //                     .ADDR
		.sram_LB_N                  (<connected-to-sram_LB_N>),                  //                     .LB_N
		.sram_UB_N                  (<connected-to-sram_UB_N>),                  //                     .UB_N
		.sram_CE_N                  (<connected-to-sram_CE_N>),                  //                     .CE_N
		.sram_OE_N                  (<connected-to-sram_OE_N>),                  //                     .OE_N
		.sram_WE_N                  (<connected-to-sram_WE_N>),                  //                     .WE_N
		.sdram_addr                 (<connected-to-sdram_addr>),                 //                sdram.addr
		.sdram_ba                   (<connected-to-sdram_ba>),                   //                     .ba
		.sdram_cas_n                (<connected-to-sdram_cas_n>),                //                     .cas_n
		.sdram_cke                  (<connected-to-sdram_cke>),                  //                     .cke
		.sdram_cs_n                 (<connected-to-sdram_cs_n>),                 //                     .cs_n
		.sdram_dq                   (<connected-to-sdram_dq>),                   //                     .dq
		.sdram_dqm                  (<connected-to-sdram_dqm>),                  //                     .dqm
		.sdram_ras_n                (<connected-to-sdram_ras_n>),                //                     .ras_n
		.sdram_we_n                 (<connected-to-sdram_we_n>),                 //                     .we_n
		.sdram_clk_clk              (<connected-to-sdram_clk_clk>),              //            sdram_clk.clk
		.system_pll_ref_reset_reset (<connected-to-system_pll_ref_reset_reset>), // system_pll_ref_reset.reset
		.system_pll_ref_clk_clk     (<connected-to-system_pll_ref_clk_clk>)      //   system_pll_ref_clk.clk
	);

