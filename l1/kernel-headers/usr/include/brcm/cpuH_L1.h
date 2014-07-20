/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This file contains the configuration parameters for qemu-mips target.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#undef CFG_HUSH_PARSER
#define CONFIG_CMD_PING        1  /* ping support                 */
#define CONFIG_NET_MULTI       1
// #define CONFIG_SERIAL_MULTI    1

#define CONFIG_MIPS32		1	/* MIPS32 CPU core */
#define CONFIG_PRC6000		1
#define CONFIG_MISC_INIT_R
/*IP address is default used by Qemu*/
#define CONFIG_SERVERIP  	192.168.15.13
#define CONFIG_IPADDR    	192.168.15.100
#define CONFIG_GATEWAYIP 	192.168.15.13
#define CONFIG_NETMASK   	255.255.255.0

/* Add'l networks stuff */
#define CONFIG_PRC6000GMAC	1
#define CONFIG_MII              1       /* MII PHY management */
#define CONFIG_CMD_MII

#define CONFIG_ETHADDR   	00:E0:0C:00:00:1
#define CFG_RX_ETH_BUFFER       20

#define CONFIG_BOOTDELAY	3 	/* autoboot after 3 seconds */

#define CONFIG_BAUDRATE		115200

/* valid baudrates */
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_TIMESTAMP		/* Print image info with timestamp */
#undef CONFIG_BOOTARGS

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"addmisc=setenv bootargs ${bootargs} "				\
		"console=ttyS0,${baudrate} "				\
		"panic=1\0"						\
	"bootfile=/vmlinux\0"				\
	"load-uboot=tftp a0100000 u-boot.bin\0"				\
	"load-linux=tftp a0300000 uImage\0"				\
	"format_u-boot=erase 0xb8000000 +60000\0"				\
	"burn_u-boot=cp.b 0xa0100000 b8000000 40000\0"				\
	""

#define CONFIG_BOOTCOMMAND	"i2c_get_temp" 

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/*
 * Command line configuration.
 */
//#include <config_cmd_default.h>

#define CONFIG_CMD_ELF
#undef CONFIG_CMD_FAT
#undef CONFIG_CMD_EXT2 
#define CONFIG_CMD_DHCP

#define CFG_NS16550
#define CFG_NS16550_SERIAL
#define CFG_NS16550_REG_SIZE	-4
#define CFG_NS16550_CLK		147450000
#define CFG_NS16550_COM1	(0xbec01800)
#define CFG_NS16550_COM2	(0xbec01c00)
#define CONFIG_CONS_INDEX	1

/*
 * Miscellaneous configurable options
 */
#define CFG_LONGHELP				/* undef to save memory */

#define CFG_PROMPT		"Percello # "	/* Monitor Command Prompt */

#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING

#define CFG_CBSIZE		256		/* Console I/O Buffer Size */
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16)  /* Print Buffer Size */
#define CFG_MAXARGS		16		/* max number of command args */

#define CFG_MALLOC_LEN		128*1024

#define CFG_BOOTPARAMS_LEN	128*1024

#define CFG_MHZ			499  // CPU clock is 26x19.2 = 499.2MHz

#define CFG_MIPS_TIMER_FREQ	(CFG_MHZ * 1000000)/2

#define CFG_HZ			1000

#define CFG_SDRAM_BASE		0xA0000000	/* Cached addr */
#define CFG_LOAD_ADDR		0xA0100000	/* default load address */

#define CFG_MEMTEST_START	0xA0100000
#define CFG_MEMTEST_END		0xA7ffffff

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

/* The following #defines are needed to get flash environment right */
#define CFG_MONITOR_BASE	TEXT_BASE 
#define CFG_MONITOR_LEN		(192 << 10)

#define CFG_INIT_SP_OFFSET	0x400000

/* We boot from this flash, selected with dip switch */
#define CFG_FLASH_BASE		0xb8000000
#define CFG_MAX_FLASH_BANKS	1
#define CFG_MAX_FLASH_SECT	512
#define CFG_FLASH_CFI		1	/* Flash memory is CFI compliant */
#define CFG_FLASH_CFI_DRIVER	1
#define CFG_FLASH_USE_BUFFER_WRITE	1

#define CFG_ENV_IS_IN_FLASH	1
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + 0x40000)

/* Address and size of Primary Environment Sector */
#define CFG_ENV_SIZE		0x20000

#define CONFIG_ENV_OVERWRITE	1

#define MEM_SIZE		128

#undef CONFIG_MEMSIZE_IN_BYTES

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE		16384 * 2
#define CFG_ICACHE_SIZE		32768 * 2
#define CFG_CACHELINE_SIZE	32

/*------------------------------------------------------------------------- */
// clockgen block
#define DDR2_END_ADDRESS                0x0FFFFFFF
#define PREFIX_CLKGEN			0xBEC02000 

#define ckg_dspce			PREFIX_CLKGEN+0x0  // DSP block en
#define ckg_cpuce			PREFIX_CLKGEN+0x4  // CPU block en 
#define ckg_cmc			    PREFIX_CLKGEN+0x8  // Clock control     
#define ckg_swrst 			PREFIX_CLKGEN+0xC  // generate SW reset   
#define ckg_rc			    PREFIX_CLKGEN+0x10 // block reset control     
#define ckg_pllgc 			PREFIX_CLKGEN+0x14 // PLL multiplexers control  
#define ckg_pll0c 			PREFIX_CLKGEN+0x18 // PLL0 control register  
#define ckg_pll1c 			PREFIX_CLKGEN+0x1C // PLL1 control register  
#define ckg_pll2c			PREFIX_CLKGEN+0x20 // PLL2 control register  
#define ckg_pll3c			PREFIX_CLKGEN+0x24 // PLL3 control register  
#define ckg_lds			    PREFIX_CLKGEN+0x28 // PLL Lock detect  
#define ckg_cpucs			PREFIX_CLKGEN+0x2C // CPU clock selector  
#define ckg_uartrrmc 		PREFIX_CLKGEN+0x30 // UART RRM clock control
#define ckg_tmr2rrmc 		PREFIX_CLKGEN+0x34 // Timer2 RRM clock control
#define ckg_dspcc 			PREFIX_CLKGEN+0x38 // DSP clock control  
#define ckg_udcc  			PREFIX_CLKGEN+0x3C // UD clock control  
#define ckg_turbocc 		PREFIX_CLKGEN+0x40 // Turbo clock control
#define ckg_daccc 			PREFIX_CLKGEN+0x44 // DAC clock control  
#define ckg_ntpcc 			PREFIX_CLKGEN+0x48 // NTP clock control  
#define ckg_ephycc 			PREFIX_CLKGEN+0x4C // EPHY / EMAC clock control 
#define ckg_rfspicc			PREFIX_CLKGEN+0x50 // RF SPI clocks control
#define ckg_tacc 			PREFIX_CLKGEN+0x54 // Time adjust settings   
#define ckg_taa  			PREFIX_CLKGEN+0x58 // Time adjust activation    
#define ckg_puss 			PREFIX_CLKGEN+0x5C // power up reason status     
#define ckg_gsmc 			PREFIX_CLKGEN+0x60 // GSM clock setting      
#define ckg_dbgc 			PREFIX_CLKGEN+0x64 // debug modes

// DSP control block
//A.T change
#define PREFIX_DSP_CONTROL			0xBE000000
#define PREFIX_DSP_DPR			    0xBE2600C8
#define HOST_DSP_MSG_INT      		0
#define HOST_DSP_GP_1		    	4
#define HOST_DSP_MSG_ACK_INT    	1

#define NEW_DSP_INTERFACE

#ifdef NEW_DSP_INTERFACE
//#warning BUILDING FOR NEW DSP-HOST INTERFACE  (offset = 1520 int = gp_1) 
#define OFFSETT 					1520
#define DSP_WRITE_INT  				HOST_DSP_GP_1
#else
#warning BUILDING FOR OLD DSP-HOST INTERFACE  (offset = 0 int = HOST<->DSP) 
#define OFFSETT 					0
#define DSP_WRITE_INT  				HOST_DSP_MSG_INT
#endif

#define PREFIX_DPRAM0				PREFIX_DSP_DPR + OFFSETT
#define PREFIX_DPRAM1				PREFIX_DSP_DPR + OFFSETT +  4
#define PREFIX_DPRAM2				PREFIX_DSP_DPR + OFFSETT +  8
#define PREFIX_DPRAM3				PREFIX_DSP_DPR + OFFSETT + 12
#define PREFIX_DPRAM4				PREFIX_DSP_DPR + OFFSETT + 16


#define PREFIX_FDP_TX_CPU			0xBE100000



#define CPU_DSP_INT					PREFIX_DSP_CONTROL+0x2000
#define CPU_MON_SEL					PREFIX_DSP_CONTROL+0x2004
#define CPU_MNBR					PREFIX_DSP_CONTROL+0x2008
#define DSP_BRKPT					PREFIX_DSP_CONTROL+0x200C
#define DSP_BOOT_EN					PREFIX_DSP_CONTROL+0x2010

		

// PAD MUX block

#define	PREFIX_PADMUX_ADDR			0xBEC02400

#define	PADMUX_REG0_ADDR			PREFIX_PADMUX_ADDR
#define	PADMUX_REG1_ADDR			PREFIX_PADMUX_ADDR+0x04
#define	PADMUX_REG2_ADDR			PREFIX_PADMUX_ADDR+0x08
#define	PADMUX_REG3_ADDR			PREFIX_PADMUX_ADDR+0x0C

#define DDR2_CSR 0xBEA00000

// ********************************************************************
// DDR2 configuration
// Option: Burst Length                  = 4
// Option: CAS Latency                   = 4
// Option: Simulation MHz                = 166
// Option: Auto Precharge Mode     (0/1) = 0
// Option: DLL Bypass Mode         (0/1) = 0
// Option: Half-Memory Support     (0/1) = 0
// Option: Registered Dimm Support (0/1) = 0
// ********************************************************************
// Memory: k4t1g164qe_e6.xml
// ********************************************************************



#define               DENALI_CTL_00_DATA 0x00000101 //0000000_0 arefresh(WR) 0000000_0 ap(RW) 00 00000_1 addr_cmp_en(RW) 0000000_1 active_aging(RW)
#define               DENALI_CTL_01_DATA 0x00010100 //0000000_0 dlllockreg(RD) 0000000_1 concurr entap(RW) 0000000_1 bank_split_en(RW) 0000000_0 auto_refresh_mode(RW)
#define               DENALI_CTL_02_DATA 0x01000100 //0000000_1 drive_dq_dqs(RW) 0000000_0 dram_ clk_disable(RW) 0000000_1 dqs_n_en(RW) 0000000_0 dll_bypass_mode(RW)
#define               DENALI_CTL_03_DATA 0x00000101 //0000000_0 intrptapburst(RW) 0000000_0 fast _write(RW) 0000000_1 enable_quick_srefresh(RW) 0000000_1 eight_bank_mode(RW)
#define               DENALI_CTL_04_DATA 0x00000000 //0000000_0 no_cmd_init(RW) 0000000_0 max_cs _reg(RD) 0000000_0 intrptwritea(RW) 0000000_0 intrptreada(RW)
#define               DENALI_CTL_05_DATA 0x01000101 //0000000_1 priority_en(RW) 0000000_0 power_ down(RW) 0000000_1 placement_en(RW) 0000000_1 odt_alt_en(RW)
#define               DENALI_CTL_06_DATA 0x01000000 //0000000_1 rw_same_en(RW) 0000000_0 reg_dim m_enable(RW) 0000000_0 reduc(RW) 0000000_0 pwrup_srefresh_exit(RW)
#define               DENALI_CTL_07_DATA 0x01010000 //0000000_1 tras_lockout(RW) 0000000_1 swap_ en(RW) 0000000_0 start(RW) 0000000_0 srefresh(RW+)
#define               DENALI_CTL_08_DATA 0x00010001 //0000000_0 write_modereg(WR) 0000000_1 writ einterp(RW) 0000000_0 weighted_round_robin_latency_control(RW) 0000000_1 tref_enable(RW)
#define               DENALI_CTL_09_DATA 0x02020000 //000000_10 axi0_w_priority(RW) 000000_10 ax i0_r_priority(RW) 000000_00 axi0_port_ordering(RW) 000000_00 axi0_fifo_type_reg(RW)
#define               DENALI_CTL_10_DATA 0x02020100 //000000_10 axi1_w_priority(RW) 000000_10 ax i1_r_priority(RW) 000000_01 axi1_port_ordering(RW) 000000_00 axi1_fifo_type_reg(RW)
#define               DENALI_CTL_11_DATA 0x02020200 //000000_10 axi2_w_priority(RW) 000000_10 ax i2_r_priority(RW) 000000_10 axi2_port_ordering(RW) 000000_00 axi2_fifo_type_reg(RW)
#define               DENALI_CTL_12_DATA 0x02020300 //000000_10 axi3_w_priority(RW) 000000_10 ax i3_r_priority(RW) 000000_11 axi3_port_ordering(RW) 000000_00 axi3_fifo_type_reg(RW)
#define               DENALI_CTL_13_DATA 0x04000002 //00000_100 caslat(RW) 00000_000 addr_pins(R W) 000000_00 weighted_round_robin_weight_sharing(RW) 000000_10 rtt_0(RW)
#define               DENALI_CTL_14_DATA 0x00000300 //00000_000 q_fullness(RW) 00000_000 port_da ta_error_type(RD) 00000_011 column_size(RW) 00000_000 cke_delay(RW)
#define               DENALI_CTL_15_DATA 0x00020203 //0000000000000_010 trtp(RW) 00000_010 trrd( RW) 00000_011 tcke(RW)
#define               DENALI_CTL_16_DATA 0x040a0f00 //0000_0100 axi0_priority0_relative_priority (RW) 0000_1010 aprebit(RW) 0000_1111 age_count(RW) 00000_000 w2r_samecs_dly(RW)
#define               DENALI_CTL_17_DATA 0x03040404 //0000_0011 axi1_priority0_relative_priority (RW) 0000_0100 axi0_priority3_relative_priority(RW) 0000_0100 axi0_priority2_relative_priority(R W) 0000_0100 axi0_priority1_relative_priority(RW)
#define               DENALI_CTL_18_DATA 0x02030303 //0000_0010 axi2_priority0_relative_priority (RW) 0000_0011 axi1_priority3_relative_priority(RW) 0000_0011 axi1_priority2_relative_priority(R W) 0000_0011 axi1_priority1_relative_priority(RW)
#define               DENALI_CTL_19_DATA 0x01020202 //0000_0001 axi3_priority0_relative_priority (RW) 0000_0010 axi2_priority3_relative_priority(RW) 0000_0010 axi2_priority2_relative_priority(R W) 0000_0010 axi2_priority1_relative_priority(RW)
#define               DENALI_CTL_20_DATA 0x08010101 //0000_1000 caslat_lin(RW) 0000_0001 axi3_pr iority3_relative_priority(RW) 0000_0001 axi3_priority2_relative_priority(RW) 0000_0001 axi3_prio rity1_relative_priority(RW)
#define               DENALI_CTL_21_DATA 0x02040f07 //0000_0010 initaref(RW) 0000_0100 dram_clas s(RW) 0000_1111 command_age_count(RW) 0000_0111 caslat_lin_gate(RW)
#define               DENALI_CTL_22_DATA 0x00000000 //0000_0000 tdfi_ctrlupd_min(RD) 0000_0000 p ort_cmd_error_type(RD) 0000_0000 max_row_reg(RD) 0000_0000 max_col_reg(RD)
#define               DENALI_CTL_23_DATA 0x00020006 //0000_0000 tdfi_rddata_en(RD) 0000_0010 tdf i_phy_wrlat_base(RW) 0000_0000 tdfi_phy_wrlat(RD) 0000_0110 tdfi_phy_rdlat(RW)
#define               DENALI_CTL_24_DATA 0x03020302 //0000_0011 wrlat(RW) 0000_0010 twtr(RW) 000 0_0011 trp(RW) 0000_0010 tdfi_rddata_en_base(RW)
#define               DENALI_CTL_25_DATA 0x00000000 //000_00000 out_of_range_type(RD) 000_00000 ocd_adjust_pup_cs_0(RW) 000_00000 ocd_adjust_pdn_cs_0(RW) 0000_0000 wrr_param_value_err(RD)
#define               DENALI_CTL_26_DATA 0x0a020906 //000_01010 trc(RW) 000_00010 tmrd(RW) 000_0 1001 tfaw(RW) 000_00110 tdal(RW)
#define               DENALI_CTL_27_DATA 0x00000003 //00_000000 port_cmd_error_id(RD) 00_000000 out_of_range_source_id(RD) 00000000 dll_lock(RD) 000_00011 twr_int(RW)
#define               DENALI_CTL_28_DATA 0x00000000 //00000000 int_ack(WR) 00000000 dll_rst_adj_ dly(RW) 0_0000000 out_of_range_length(RD) 00_000000 port_data_error_id(RD)
#define               DENALI_CTL_29_DATA 0x16030802 //00010110 trfc(RW) 00000011 trcd_int(RW) 00 001000 tras_min(RW) 00000010 tmod(RW)
#define               DENALI_CTL_30_DATA 0x00000000 //0000000_000000000 int_status(RD) 0000000_0 00000000 int_mask(RW)
#define               DENALI_CTL_31_DATA 0x00640064 //000000_0001100100 axi1_priority_relax(RW) 000000_0001100100 axi0_priority_relax(RW)
#define               DENALI_CTL_32_DATA 0x00640064 //000000_0001100100 axi3_priority_relax(RW) 000000_0001100100 axi2_priority_relax(RW)
#define               DENALI_CTL_33_DATA 0x00000040 //000_0000000000000 emrs2_data_0(RW) 000_000 0001000000 emrs1_data_0(RW)
#define               DENALI_CTL_34_DATA 0x04420000 //000_0010001000010 mrs_data_0(RW) 000_00000 00000000 emrs3_data_0(RW)
#define               DENALI_CTL_35_DATA 0x00000000 //00_00000000000000 tdfi_phyupd_resp(RD) 00_ 00000000000000 tdfi_ctrlupd_max(RD)
#define               DENALI_CTL_36_DATA 0x050e0000 //00_00010100001110 tref(RW) 00_000000000000 00 tdfi_phyupd_type0(RD)
#define               DENALI_CTL_37_DATA 0x00010001 //0000000000000001 axi1_en_size_lt_width_ins tr(RW) 0000000000000001 axi0_en_size_lt_width_instr(RW)
#define               DENALI_CTL_38_DATA 0x00010001 //0000000000000001 axi3_en_size_lt_width_ins tr(RW) 0000000000000001 axi2_en_size_lt_width_instr(RW)
#define               DENALI_CTL_39_DATA 0x00430000 //0000000001000011 tcpd(RW) 0000000000000000  dll_rst_delay(RW)
#define               DENALI_CTL_40_DATA 0x000200c8 //0000000000000010 tpdex(RW) 000000001100100 0 tdll(RW)
#define               DENALI_CTL_41_DATA 0x00172d89 //0000000000010111 txsnr(RW) 001011011000100 1 tras_max(RW)
#define               DENALI_CTL_42_DATA 0x000000c8 //0000000000000000 version(RD) 0000000011001 000 txsr(RW)
#define               DENALI_CTL_43_DATA 0x00008236 //00000000000000001000001000110110 tinit(RW) 
#define               DENALI_CTL_44_DATA 0x00000000 //0_0000000000000000000000000000000 out_of_r ange_addr(RD)
#define               DENALI_CTL_45_DATA 0x00000000 //0_0000000000000000000000000000000 port_cmd _error_addr(RD)
#define               DENALI_CTL_46_DATA 0x00000000 //00000000000000000000000000000000 dft_ctrl_ reg(RW)
#define               DENALI_CTL_47_DATA 0x00121e36 //00000000000100100001111000110110 dll_ctrl_ reg_0_0(RW)
#define               DENALI_CTL_48_DATA 0x00121e36 //00000000000100100001111000110110 dll_ctrl_ reg_0_1(RW)
#define               DENALI_CTL_49_DATA 0x00121e36 //00000000000100100001111000110110 dll_ctrl_ reg_0_2(RW)
#define               DENALI_CTL_50_DATA 0x00121e36 //00000000000100100001111000110110 dll_ctrl_ reg_0_3(RW)
#define               DENALI_CTL_51_DATA 0x00385f0f //00000000001110000101111100001111 dll_ctrl_ reg_1_0(RW)
#define               DENALI_CTL_52_DATA 0x00385f0f //00000000001110000101111100001111 dll_ctrl_ reg_1_1(RW)
#define               DENALI_CTL_53_DATA 0x00385f0f //00000000001110000101111100001111 dll_ctrl_ reg_1_2(RW)
#define               DENALI_CTL_54_DATA 0x00385f0f //00000000001110000101111100001111 dll_ctrl_ reg_1_3(RW)
#define               DENALI_CTL_55_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_0_0(RD)
#define               DENALI_CTL_56_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_0_1(RD)
#define               DENALI_CTL_57_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_0_2(RD)
#define               DENALI_CTL_58_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_0_3(RD)
#define               DENALI_CTL_59_DATA 0x000f0133 //00000000000011110001000100110011 pad_ctrl_ reg_0(RW) - programming Standard Pad model (75ohm)
#define               DENALI_CTL_60_DATA 0xf3014b26 //11110011000000010100101100100110 phy_ctrl_ reg_0_0(RW)
#define               DENALI_CTL_61_DATA 0xf3014b26 //11110011000000010100101100100110 phy_ctrl_ reg_0_1(RW)
#define               DENALI_CTL_62_DATA 0xf3014b26 //11110011000000010100101100100110 phy_ctrl_ reg_0_2(RW)
#define               DENALI_CTL_63_DATA 0xf3014b26 //11110011000000010100101100100110 phy_ctrl_ reg_0_3(RW)
#define               DENALI_CTL_64_DATA 0x07c00301 //00000111110000000000001100000001 phy_ctrl_ reg_1_0(RW)
#define               DENALI_CTL_65_DATA 0x07c00301 //00000111110000000000001100000001 phy_ctrl_ reg_1_1(RW)
#define               DENALI_CTL_66_DATA 0x07c00301 //00000111110000000000001100000001 phy_ctrl_ reg_1_2(RW)
#define               DENALI_CTL_67_DATA 0x07c00301 //00000111110000000000001100000001 phy_ctrl_ reg_1_3(RW)
#define               DENALI_CTL_68_DATA 0x00000004 //00000000000000000000000000000100 phy_ctrl_ reg_2(RW)
#define               DENALI_CTL_69_DATA 0x00000000 //00000000000000000000000000000000 phy_obs_r eg_0_0(RD)
#define               DENALI_CTL_70_DATA 0x00000000 //00000000000000000000000000000000 phy_obs_r eg_0_1(RD)
#define               DENALI_CTL_71_DATA 0x00000000 //00000000000000000000000000000000 phy_obs_r eg_0_2(RD)
#define               DENALI_CTL_72_DATA 0x00000000 //00000000000000000000000000000000 phy_obs_r eg_0_3(RD)
#define               DENALI_CTL_73_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_74_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_75_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_76_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_77_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_78_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_79_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_80_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_81_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_82_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_83_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_84_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_85_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_86_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_87_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_88_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_89_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_90_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_91_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_92_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_93_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_94_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_95_DATA 0x00000000 //00000000000000000000000000000000 obsolete_ placeholder(RW)
#define               DENALI_CTL_96_DATA 0x03040000 //0000_0011 wrlat_adj(RW) 0000_0100 rdlat_ad j(RW) 0_000000000000000
#define               DENALI_CTL_97_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_1_0(RD)
#define               DENALI_CTL_98_DATA 0x00000000 //00000000000000000000000000000000
#define               DENALI_CTL_99_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_100_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_101_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_102_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_1_1(RD)
#define              DENALI_CTL_103_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_104_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_105_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_106_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_107_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_1_2(RD)
#define              DENALI_CTL_108_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_109_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_110_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_111_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_112_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_1_3(RD)
#define              DENALI_CTL_113_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_114_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_115_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_116_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_117_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_2_0(RD)
#define              DENALI_CTL_118_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_119_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_120_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_121_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_122_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_2_1(RD)
#define              DENALI_CTL_123_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_124_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_125_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_126_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_127_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_2_2(RD)
#define              DENALI_CTL_128_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_129_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_130_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_131_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_132_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_2_3(RD)
#define              DENALI_CTL_133_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_134_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_135_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_136_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_137_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_3_0(RD)
#define              DENALI_CTL_138_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_139_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_140_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_141_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_142_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_3_1(RD)
#define              DENALI_CTL_143_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_144_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_145_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_146_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_147_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_3_2(RD)
#define              DENALI_CTL_148_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_149_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_150_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_151_DATA 0x00000000 //00000000000000000000000_000000000
#define              DENALI_CTL_152_DATA 0x00000000 //00000000000000000000000000000000 dll_obs_r eg_3_3(RD)
#define              DENALI_CTL_153_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_154_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_155_DATA 0x00000000 //00000000000000000000000000000000
#define              DENALI_CTL_156_DATA 0x00000000 //00000000000000000000000_000000000

//////////////////////////////////////////////////////////
// GPIO block
#define PREFIX_GPIO		0xBEC01400 
#define gpio_swporta_dr		PREFIX_GPIO+0x0  // port A output data
#define gpio_swporta_ddr	PREFIX_GPIO+0x4  // port A direction
#define gpio_swportb_dr		PREFIX_GPIO+0xC  // port B output data
#define gpio_swportb_ddr	PREFIX_GPIO+0x10 // port B direction
//////////////////////////////////////////////////////////
// PADC block
#define PREFIX_PADC		0xBEC02400 
#define padc_selector		PREFIX_PADC+0x0  // PadcC selector register
#define padc_control		PREFIX_PADC+0x4  // PadcC pad control register
#define padc_lvds		PREFIX_PADC+0x8  // PadcC LVDS pad control register
#define padc_ddr_ephy		PREFIX_PADC+0xC  // PadcC ddr & ephy pad control register

#endif /* __CONFIG_H */
