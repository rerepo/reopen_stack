#ifndef BRCM_FSM_H
#define BRCM_FSM_H



typedef struct {
	unsigned long 	otpmem[64];
} brcm_fsm_params_t; 
 
#define OTPMEM_SIZE			64*sizeof(unsigned long)
 


#define PROG_OK_RES   0x14


/* system call command macros */
#define FSM_RELOAD_FOUT				0
#define FSM_READ_BIT					1
#define FSM_READ_ALL					2
#define FSM_PROG_ENABLE       2
#define FSM_PROG_DISABLE			3
#define FSM_PROG_BIT					4
#define FSM_PROG_SEC1					5
#define FSM_PROG_SEC2			  	6
#define FSM_PROG_SEC3					7
#define FSM_PROG_SEC4  				8

#ifdef __KERNEL__

#include "brcm_dsp.h"
#include "brcm_hal.h"
#include "celivero_cpuh.h"
/* Control REG bits */
/*0-3  */	#define FSM_CTRL_REG_CMD_BF											0xF
					#define FSM_CTRL_REG_CMD_RELOAD_FOUT_BIT		  	0x0		
					#define FSM_CTRL_REG_CMD_PRE_SCREEN_BIT 				0x1 
					#define FSM_CTRL_REG_CMD_READ_BIT_BIT						0x2  
					#define FSM_CTRL_REG_CMD_READ_ALL_BIT						0x3  
					#define FSM_CTRL_REG_CMD_PROG_ENABLE_BIT      	0x4
					#define FSM_CTRL_REG_CMD_PROG_DISABLE_BIT				0x5
					#define FSM_CTRL_REG_CMD_PROG_BIT_BIT						0x6
					#define FSM_CTRL_REG_CMD_OVST_READ_BIT					0x8
					#define FSM_CTRL_REG_CMD_OVST_PROG_BIT					0x9
					#define FSM_CTRL_REG_CMD_PROG_SEC1_BIT					0xC
					#define FSM_CTRL_REG_CMD_PROG_SEC2_BIT		  		0xD
					#define FSM_CTRL_REG_CMD_PROG_SEC3_BIT					0xE
					#define FSM_CTRL_REG_CMD_PROG_SEC4_BIT 					0xF
/* 4 */ 	#define FSM_CTRL_REG_CMD_START_BIT   						0x10
/* 5 */ 	#define FSM_CTRL_REG_DEBUG_MODE_BIT	 				  	0x20
/*6-7*/ 	/* TBD */
/*8-9*/ 	#define FSM_CTRL_REG_FUSE_RD_MODE_BF          	0x300
        	#define FSM_CTRL_REG_FUSE_RD_MODE_OR_BIT		  	0x000  
        	#define FSM_CTRL_REG_FUSE_RD_MODE_READ_1_BIT  	0x100  
        	#define FSM_CTRL_REG_FUSE_RD_MODE_READ_2_BIT  	0x200  
        	#define FSM_CTRL_REG_FUSE_RD_MODE_RESERVE_BIT 	0x300  
/*10-11*/ #define FSM_CTRL_REG_FUSE_WR_MODE_BF          	0xC00
        	#define FSM_CTRL_REG_FUSE_WR_MODE_AT_LST_1_BIT	0x000  
        	#define FSM_CTRL_REG_FUSE_WR_MODE_PROG_BOTH_BIT	0x400  
        	#define FSM_CTRL_REG_FUSE_WR_MODE_PROG_0_BIT  	0x800  
        	#define FSM_CTRL_REG_FUSE_WR_MODE_PROG_1_bit   	0xC00  
/*12-13*/ /* TBD */        
/*14   */ #define FSM_CTRL_REG_DSP_LD_ENB_CTL_BIT					0x4000
/*15   */ #define FSM_CTRL_REG_DBG_SW_CTL_BIT							0x8000
/*16-26*/ #define FSM_CTRL_REG_REQ_ADDR_MODE_BF          	0x7FF0000 
          #define FSM_CTRL_REG_REQ_ADDR_MODE_SHIFT_MASK   16
/*27-30*/ /* TBD */        
/*31   */ #define FSM_CTRL_REG_REQ_TEST_COL_BIT						0x80000000
        
        

/* STATUS REG bits */
/* 0   */  #define FSM_STATUS_REG_WRP_BUSY_BIT						0x1
/* 1   */  /* TBD */
/* 2   */  #define FSM_STATUS_REG_PROG_OK_BIT							0x4
/* 3   */  #define FSM_STATUS_REG_REF_OK_BIT							0x8
/* 4   */  #define FSM_STATUS_REG_FOUT_VALID_BIT					0x10
/* 5   */  #define FSM_STATUS_REG_PROG_FAIL_BIT						0x20
/* 6   */  #define FSM_STATUS_REG_PRESCREEN_FAIL_BIT			0x40
/* 7   */  #define FSM_STATUS_REG_RD_BIT									0x80
/* 8   */  #define FSM_STATUS_REG_TST_COL_RD_BIT					0x100
/* 9   */  #define FSM_STATUS_REG_PROG_NOT_ALLOWD_BIT			0x200
/* 10  */  #define FSM_STATUS_REG_BAD_COMMAND_BIT					0x400
/*11-15*/  /* TBD */
/*16-27*/  #define FSM_STATUS_REG_ERR_BIT_ADDR_BIT  			0xFFF0000
/*28-29*/  /* TBD */
/*30   */  #define FSM_STATUS_REG_ERR_FUSE_BIT  					0x40000000
/*31   */  #define FSM_STATUS_REG_ERR_TESTCOL_BIT 				0x80000000
        
#define FSM_SUCCESS									0


#define	FSM_BASE_ADDR								(0xBEC02C00)	

/* registers */
#define	FSM_OTP_MEM_ADDR						(FSM_BASE_ADDR+0x000)
#define	FSM_CONTROL_REG_ADDR				(FSM_BASE_ADDR+0x100)
#define	FSM_STATUS_REG_ADDR					(FSM_BASE_ADDR+0x104)
#define	FSM_CONFIG_REG_ADDR					(FSM_BASE_ADDR+0x108)

#define WAIT_FOR_READY_TIMEOUT			0x10000


#define DEBUG
#ifdef DEBUG
	#define PRINTK printk
#else
	#define PRINTK(_x,...) 
#endif



static inline int read_rwp_ready_bit(void)
{
	int rb = celivero_readl(FSM_STATUS_REG_ADDR) & FSM_STATUS_REG_WRP_BUSY_BIT;
	PRINTK("%x >> %x\n",FSM_STATUS_REG_ADDR,rb);
	return (rb);
}

static inline int is_wrp_ready(void)
{
	volatile u32 timeout_cnt = 0;
	volatile u16 ready;
	do
	{
		ready = read_rwp_ready_bit();
	} while((timeout_cnt++<WAIT_FOR_READY_TIMEOUT) && (ready));
	return !ready;
}

static inline int  is_fout_valid(void)
{
	return ( celivero_readl(FSM_STATUS_REG_ADDR) & FSM_STATUS_REG_FOUT_VALID_BIT);
}

static inline int do_cmd(u32 cmd,u32 pass_criteria)
{
	int ret;
	cmd |= FSM_CTRL_REG_CMD_START_BIT;
	if(is_wrp_ready())
	{
		celivero_writel(cmd,FSM_CONTROL_REG_ADDR);
		PRINTK("%x << %x\n",FSM_CONTROL_REG_ADDR,cmd);
		if(celivero_readl(FSM_STATUS_REG_ADDR)==pass_criteria)
				ret = FSM_SUCCESS;
		PRINTK("%x >> %x\n",FSM_STATUS_REG_ADDR,celivero_readl(FSM_STATUS_REG_ADDR));
	}
	else
	{
		ret = -EFAULT;
	}		
	return ret;
}
 
 
 
#ifdef __BRCM_FSM__
static int fsm_reload_fout(void);
static int fsm_read_bit(void);
static int fsm_read_all(void);
static int fsm_cmd_demux(unsigned long cmd, unsigned long arg,void *arg1);
static int __init fsm_driver_init_module (void);
static void __exit fsm_driver_cleanup_module (void);
#define EXTERN 
#else
#define EXTERN extern
#endif

#undef EXTERN



 #endif



#endif
