#ifndef BRCM_DRIVERS_H
#define BRCM_DRIVERS_H


#define GET_DRIVER_IDX(a)   ((a & 0xFFFF0000)>>16)
#define GET_DRIVER_CMD(a)   (a & 0xFFFF)
#define SET_DRIVER_IDX(a)   ((a) << 16)
#define SET_DRIVER_CMD(a)   ((a) & 0x0000ffff)

#define SET_SYSCALL_CMD(a,b) (SET_DRIVER_IDX(a) | SET_DRIVER_CMD(b) )


typedef enum {
   BRCM_DRIVER_FLE = 0,
   BRCM_DRIVER_TTI,
   BRCM_DRIVER_DPR,
   BRCM_DRIVER_DMA, 
   BRCM_DRIVER_MMAP,
   BRCM_DRIVER_LOGGER,    
   BRCM_DRIVER_DSP,
   BRCM_DRIVER_FRAME_CAPTURE,
   BRCM_DRIVER_F8,
   BRCM_DRIVER_READ_FSM,
   BRCM_DRIVER_AES,
   BRCM_DRIVER_SHA,
   BRCM_DRIVER_FSM,
   BRCM_DRIVER_TURBO,
   BRCM_DRIVER_1PPS,
   BRCM_DRIVER_PRINTK,
#ifdef CONFIG_MAC_FILTER
   BRCM_DRIVER_MAC,
#endif
   BRCM_DRIVER_CPU_IPC,
   BRCM_DRIVER_MMAP_IPC,
   BRCM_DRIVER_F8_2,
   BRCM_DRIVER_SNIFFER,
   BRCM_DRIVER_RSA,
   BRCM_DRIVER_TURBO_2,
   BRCM_DRIVER_FASTSOCK,
   BRCM_DRIVER_WD,
   BRCM_MAX_DRIVER_IDX
} brcm_drivers_e;


typedef struct {
  brcm_drivers_e driver_idx;
  int (*driver_syscall_hook)(unsigned long,unsigned long, void *);
} brcm_driver_register_t;

#ifdef __BRCM_DRIVER__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int register_brcm_driver(brcm_driver_register_t *drv_reg);


#undef EXTERN
#endif
