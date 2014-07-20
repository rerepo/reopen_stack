#ifndef __BRCM_WD_H__
#define __BRCM_WD_H__

#define WD_KICK_WITH_PARAMS  		0x0 
#define WD_KICK_MAX_PARAMS      0x1
#define WD_REARM								0x2
#define WD_SET_TOUT						  0x3
#define WD_STOP							    0x4

 
#define	WDT_BASE_ADDR						(0xBEC01000)                                        
                                                                                  
/* registers */                                                                   
#define	WDT_CTR_REG_ADDR				(WDT_BASE_ADDR+0x00)	// Control Reg              
#define	WDT_TORR_REG_ADDR				(WDT_BASE_ADDR+0x04)	// Timeout Range Reg        
#define	WDT_CCVR_REG_ADDR				(WDT_BASE_ADDR+0x08)	// Current Counter Value Reg
#define	WDT_CRR_REG_ADDR				(WDT_BASE_ADDR+0x0C)	// Counter Restart Reg      
#define	WDT_STAT_REG_ADDR				(WDT_BASE_ADDR+0x10)	// Interrupt Status Reg     
#define	WDT_EOI_REG_ADDR				(WDT_BASE_ADDR+0x14)	// Interrupt Clear Reg      
#define	WDT_COMP_PARAMS					(WDT_BASE_ADDR+0xF4)	// Component params			    

#endif //__BRCM_
