#ifndef BRCM_LOGGER_H
#define BRCM_LOGGER_H

#include "brcm_l1_common_interface.h"
#include "brcm_hal.h"
#ifdef __KERNEL__
#include <linux/sched.h>
#include <linux/pid.h>
#endif


/* ================ FOR PROFILING ======================== */
#define M_PERFCTL_EXL			(1UL      <<  0)
#define M_PERFCTL_KERNEL		(1UL      <<  1)
#define M_PERFCTL_SUPERVISOR		(1UL      <<  2)
#define M_PERFCTL_USER			(1UL      <<  3)
#define M_PERFCTL_INTERRUPT_ENABLE	(1UL      <<  4)
#define M_PERFCTL_EVENT(event)		(((event) & 0x3ff)  << 5)
#define M_PERFCTL_VPEID(vpe)		((vpe)    << 16)
#define M_PERFCTL_MT_EN(filter)		((filter) << 20)
#define    M_TC_EN_ALL			M_PERFCTL_MT_EN(0)
#define    M_TC_EN_VPE			M_PERFCTL_MT_EN(1)
#define    M_TC_EN_TC			M_PERFCTL_MT_EN(2)
#define M_PERFCTL_TCID(tcid)		((tcid)   << 22)
#define M_PERFCTL_WIDE			(1UL      << 30)
#define M_PERFCTL_MORE			(1UL      << 31)

#define M_COUNTER_OVERFLOW		(1UL      << 31)

#define PERFCNT_EVENTMASK                0x000007e0
#define PERFCNT_IE                      0x00000010
#define PERFCNT_U                       0x00000008
#define PERFCNT_S                        0x00000004
#define PERFCNT_K                       0x00000002
#define PERFCNT_EXL                   0x00000001
#define C0_PERFCNT     25

#define PERFCNT_EVENTSHFT 5

#define PERFCNT_EV_CYCLES 0
#define PERFCNT_EV_ICOMPLETE 1
#define ICACHE_ACCESS 10
#define DCACHE_ACCESS 12

#define DCACHE_LOADS 14
#define DCACHE_STORES 15

#define EXC_INT 26

#define L2_ACCESS 28

#define NON_CACHE 35

#define NO_ASID 0x40003000

#define SetPerfCtl0(val) _m32c0_mtc0(C0_PERFCNT,0,val)
#define SetPerfCtl1(val) _m32c0_mtc0(C0_PERFCNT,2,val)
#define SetPerfCnt0(val) _m32c0_mtc0(C0_PERFCNT,1,val)
#define SetPerfCnt1(val) _m32c0_mtc0(C0_PERFCNT,3,val)
#define GetPerfCnt0()		 _m32c0_mfc0(C0_PERFCNT,1)
#define GetPerfCnt1() 	 _m32c0_mfc0(C0_PERFCNT,3)

#define GetPerfCtl0() 	 _m32c0_mfc0(C0_PERFCNT,0)
#define GetFreeCnt() 		 _m32c0_mfc0(9,0)
#define GetSleepCnt() 	 _m32c0_mfc0(22,7)
#define GetWaitCountX()   _m32c0_mfc0(9,6)
#define GetWaitCount()   _m32c0_mfc0(9,7)

#define SetPerfCtl2(val) _m32c0_mtc0(C0_PERFCNT,4,val)
#define SetPerfCtl3(val) _m32c0_mtc0(C0_PERFCNT,6,val)
#define SetPerfCnt2(val) _m32c0_mtc0(C0_PERFCNT,5,val)
#define SetPerfCnt3(val) 						_m32c0_mtc0(C0_PERFCNT,7,val)
#define GetPerfCnt2() 						 _m32c0_mfc0(C0_PERFCNT,5)
#define GetPerfCnt3() 						 _m32c0_mfc0(C0_PERFCNT,7)

#define GetStatusRegister()         _m32c0_mfc0(12, 0) 
#define GetConfigRegister()         _m32c0_mfc0(16, 0) 
#define GetConfig1Register()        _m32c0_mfc0(16, 1) 
#define GetConfig2Register()        _m32c0_mfc0(16, 2) 
#define GetConfig3Register()        _m32c0_mfc0(16, 3) 
#define GetBroadcomConfigRegister() _m32c0_mfc0(22, 0) 
#define GetBroadcomModeRegister()   _m32c0_mfc0(22, 1) 
#define GetInstCacheErrorRegister() _m32c0_mfc0(27, 0) 
#define GetDataCacheErrorRegister() _m32c0_mfc0(27, 1) 





#define _m32c0_mfc0(reg, sel) \
({ \
  register unsigned long __r; \
  __asm__ __volatile ("mfc0 %0,$%1,%2" \
                                      : "=d" (__r) \
                                      : "JK" (reg), "JK" (sel)); \
  __r; \
})

#define _m32c0_mtc0(reg, sel, val) \
do { \
    __asm__ __volatile ("%(mtc0 %z0,$%1,%2; ssnop; ssnop; ssnop%)" \
                                                : \
                                                : "dJ" ((unsigned long)(val)), "JK" (reg), "JK" (sel) \
                                                : "memory"); \
} while (0)




#define BRCM_LOG_PID_HISTORY_MAX_ENTRIES	100
#define BRCM_LOG_PID_HISTORY_MAX_BYTES		(BRCM_LOG_PID_HISTORY_MAX_ENTRIES * (256+4)) /* 256 length of string + 4 bytes of PID */
#define BRCM_LOG_BUFFER_MAX_ENTRIES			16384
#define BRCM_LOG_BUFFER_MAX_BYTES			(512*1024 - (4 + BRCM_LOG_PID_HISTORY_MAX_BYTES)) /* 512 KB minus index and PID history */
#define INT_CONTEXT							0xFFFFFFFF
#define CLOCK_TERM_VALUE					0x124F7FF

#define START_UTC							0
#define GET_INDEX							1
#define START_LOG							2
#define STOP_LOG							3
#define GET_UTC								4
#define LOG_FUNCTION						5
#define GET_LOG								6
#define GET_PID_HISTORY						7
#define GET_PERF_COUNT						8
#define GET_PERF_SLEEP						9
#define GET_PERF_WAIT						10
#define	GET_PERF_WAITX						11
#define GET_CPU_FREQ						12
#define GET_CPU_COUNT						13
#define GET_FREE_MEM						14


typedef enum {
	EVENT_GENERIC,
	EVENT_IRQ_TIMER,
	EVENT_IRQ_SMP_SCHEDULER,
	EVENT_IRQ_SMP_CALL_FUNCTION,
	EVENT_IRQ_TTI,
	EVENT_IRQ,
	EVENT_TASK_SWITCH,
	EVENT_USER,
	EVENT_DMA,
	EVENT_BRCM_DMA,
	EVENT_TASK_SWITCH_PC_PREV,
	EVENT_TASK_SWITCH_PC_NEXT,
	EVENT_NET_RX,
#ifdef CONFIG_BCM617xx_LOG_EXTRA
	EVENT_SOCKET,
	EVENT_IPSEC,
	EVENT_ETH,
#endif	// CONFIG_BCM617xx_LOG_EXTRA
	// Don't forget to add an entry below to 'event_str' array.
	// Leave this here.
	EVENT_NUM
} EVENT_TYPES;



#ifdef __LOGGER_INTERNAL__

typedef struct
{
	int num;
	const char *name;
} event_struct;

#undef EVT
#define EVT(x) { x, STR(x) }

static const event_struct event_str[] = {
	EVT(EVENT_GENERIC),
	EVT(EVENT_IRQ_TIMER),
	EVT(EVENT_IRQ_SMP_SCHEDULER),
	EVT(EVENT_IRQ_SMP_CALL_FUNCTION),
	EVT(EVENT_IRQ_TTI),
	EVT(EVENT_IRQ),
	EVT(EVENT_TASK_SWITCH),
	EVT(EVENT_USER),
	EVT(EVENT_DMA),
	EVT(EVENT_BRCM_DMA),
	EVT(EVENT_TASK_SWITCH_PC_PREV),
	EVT(EVENT_TASK_SWITCH_PC_NEXT),
	EVT(EVENT_NET_RX),
#ifdef CONFIG_BCM617xx_LOG_EXTRA
	EVT(EVENT_SOCKET),
	EVT(EVENT_IPSEC),
	EVT(EVENT_ETH),
#endif	//CONFIG_BCM617xx_LOG_EXTRA
};

#endif

#ifdef CONFIG_BCM617xx_LOGGER
	#define BCM_LOG(event, data) \
		if(brcm_logger_kernel_hook) \
			brcm_logger_kernel_hook(event, data, __FILE__, __LINE__)
#else
	#define BCM_LOG(event, data)
#endif

extern void (*brcm_logger_kernel_hook)(unsigned long event, unsigned long payload, const char *file, int line);


#ifdef CONFIG_BRCM_SYSCALL_PROFILING

static inline void brcm_read_utc(brcm_utc_t *ts)
{
#ifdef D_CPU_TYPE_CPUH
		 /* start the UTC */
		/* ... */
#endif
#ifdef D_CPU_TYPE_CPUL
		 /* start the UTC */
		 /* ... */
#endif
#if 0
	 ts->usec = (PRC_CPU_READ(0xBFE01420)*100)/1920;
     ts->sec  = PRC_CPU_READ(0xBFE0141c);
#endif
}
static inline unsigned long prc_utc_timediff(brcm_utc_t *ts_start,brcm_utc_t *ts_end)
{
	 unsigned long long temp_start,temp_end;
     temp_start = (ts_start->sec  * 1000000ULL) + ts_start->usec;
	 temp_end = (ts_end->sec  * 1000000ULL) + ts_end->usec;
	 return ((unsigned long)(temp_end-temp_start));
}


#endif 

typedef struct {
	unsigned long			sec;
	unsigned long			usec;
} brcm_utc_t;

#pragma pack(4)
typedef struct {
	union {
		union
		{
			struct {
				unsigned long timestamp_low;
				unsigned long timestamp_high;
			} ts;
			unsigned long long timestamp;
		};
		brcm_utc_t		utc;
		unsigned long c0_count;
	};

	unsigned long   cpu : 1,    // 1 bit for cpu number
					event : 31; // 31 bits for event (more than enough++)

	unsigned long payload;
	unsigned long counter;
	unsigned long line;

	// File name must be the last entry!
	const char *file;
#ifndef __KERNEL__
	char file_name[256];
#endif
}  log_entry_t;
#pragma pack()

#pragma pack(4)
typedef struct {
	unsigned long pid;
	char name[256];
} pid_history_t;
#pragma pack()

#ifdef __KERNEL__

#ifdef __LOGGER_INTERNAL__
#define EXTERN
#else
#define EXTERN extern
#endif

#ifdef CONFIG_BRCM_DUMP_LOGGER_ON_PANIC	
extern void (*brcm_logger_from_panic_hook)(int);
#endif

/* Fast logger */

/* Memory map for logger (per CPU):
 *
 * [0x00000000 - 0x00000004] = Current logger index = 0x4 bytes
 * [0x00000004 - 0x00006594] = PID history (100 strings * 260 length each string) = 0x6590 bytes
 * [0x00006594 - 0x00076594] = Buffer data (28 byte struct * 16384 entries) = 0x70000 bytes
 *
 * Base offset for CPU-H: 0x8fe00000
 * Base offset for CPU-L: 0x8fe80000
 */

#if defined(D_CPU_TYPE_CPUL) || defined(CONFIG_ZEPHYR)
	#define BRCM_LOG_BASE_ADDR				(0x8fe80000)
	//#define BRCM_LOG_BASE_ADDR				(0xafe80000)
	#define BRCM_LOG_OTHER_CPU_BASE_ADDR	(0xafe00000)
#else
	#define BRCM_LOG_BASE_ADDR				(0x8fe00000)
	//#define BRCM_LOG_BASE_ADDR				(0xafe00000)
	#define BRCM_LOG_OTHER_CPU_BASE_ADDR	(0xafe80000)
#endif

#define brcm_log_index					((unsigned long *)BRCM_LOG_BASE_ADDR)
#define brcm_log_pid_history			((pid_history_t *)(((unsigned long)brcm_log_index) + 4))
#define brcm_log_buffer					((log_entry_t   *)(((unsigned long)brcm_log_pid_history) + BRCM_LOG_PID_HISTORY_MAX_BYTES))

#define brcm_log_index_other_cpu		((unsigned long *)BRCM_LOG_OTHER_CPU_BASE_ADDR)
#define brcm_log_pid_history_other_cpu	((pid_history_t *)(((unsigned long)brcm_log_index_other_cpu) + 4))
#define brcm_log_buffer_other_cpu		((log_entry_t   *)(((unsigned long)brcm_log_pid_history_other_cpu) + BRCM_LOG_PID_HISTORY_MAX_BYTES))

EXTERN unsigned long 			brcm_log_logging;
EXTERN raw_spinlock_t 			logger_counter_lock;
//EXTERN unsigned long 			*brcm_log_index;
EXTERN unsigned long 			brcm_log_counter;
//EXTERN log_entry_t				*brcm_log_buffer;
EXTERN int			 			brcm_log_is_mctu_active;

/* String logger */

#define	MAX_BCM_LOG_STR			192
#define	BCM_LOG_MAX_IDX			1000

typedef enum {
	BCM_LOG_MODULE_DMA,
	BCM_LOG_MODULE_SNIFFER,
	BCM_LOG_MODULE_RSA,
	BCM_LOG_MODULE_LOGGER,
	BCM_LOG_MODULE_NUM
} BCM_LOG_MODULES;

#define bcm_info(format, ...)		bcm_log_internal(BCM_MODULE, 0, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define bcm_err(format, ...)		bcm_log_internal(BCM_MODULE, 1, __FILE__, __LINE__, format, ##__VA_ARGS__)

#ifdef __ENABLE_BCM_DEBUG__
	#define bcm_dbg(format, ...)	bcm_log_internal(BCM_MODULE, 2, __FILE__, __LINE__, format, ##__VA_ARGS__)
#else
	#define bcm_dbg(format, ...)
#endif

EXTERN void bcm_log_internal(int module, int severity, const char *file, int line, char *fmt, ...);

EXTERN u16 bcm_logger_idx[BCM_LOG_MODULE_NUM];
EXTERN u8 bcm_log_buffer[BCM_LOG_MODULE_NUM][BCM_LOG_MAX_IDX][MAX_BCM_LOG_STR + 64];
EXTERN struct mutex bcm_log_mutex;
EXTERN u8 bcm_logger_on[BCM_LOG_MODULE_NUM];
EXTERN u8 bcm_logger_event_on[EVENT_NUM];
EXTERN int bcm_print_log(char *page, char **start, off_t off, int count, int *eof, void *data);

/*
* =======================================================================================
*  
* 
* =======================================================================================
*/
static __inline__ unsigned long brcm_logger_get_timestamp_high(void)
{
	return PRC_CPU_READ(MCTU_READ_MFC);
	//return PRC_CPU_READ(0xBFE0141c);
}
/*
* =======================================================================================
*  
* 
* =======================================================================================
*/
static __inline__ unsigned long brcm_logger_get_timestamp_low(void)
{
	return PRC_CPU_READ(MCTU_READ_MCC);	
	//return PRC_CPU_READ(0xBFE01420);
}
/*
* =======================================================================================
* Dump N entries from log starting at the latest entry. Incase read_log can not be
*  executed (freeze)
* =======================================================================================
*/
void static __inline__ __brcm_logger_dump_logger(int number)
{
		u32 		idx;
		int 		i;
		
		brcm_log_logging = 0;	
		idx = *brcm_log_index;
		for(i = 0; i < number;i++)
		{
			printk("%10x %10x %10x %10x %10x\n", (unsigned int)brcm_log_buffer[idx].counter,
  		                                     (unsigned int)brcm_log_buffer[idx].ts.timestamp_high,
			                                     (unsigned int)brcm_log_buffer[idx].ts.timestamp_low,
  		                                     (unsigned int)brcm_log_buffer[idx].event,
	  	                                     (unsigned int)brcm_log_buffer[idx].payload);
	  	if(idx == 0) 
	  		idx= BRCM_LOG_BUFFER_MAX_ENTRIES - 1;                                    
	  	else
	  		idx = idx - 1 ;
		}
}

/*
* =======================================================================================
* This is the main logging function.  Notice the use of the spinlock_irq protected temp 
* counter to cater for preemtion (from interrupt context and/or other tasks).
* =======================================================================================
*/
void static __inline__ brcm_logger_log_event(unsigned long event, unsigned long payload, const char *file, int line)
{
	unsigned long 		flags;
	unsigned long 		index;

	if (unlikely(brcm_log_logging && bcm_logger_event_on[event]))
	{
		raw_spin_lock_irqsave(&logger_counter_lock, flags);
		*brcm_log_index = (*brcm_log_index + 1) % BRCM_LOG_BUFFER_MAX_ENTRIES;
		index = *brcm_log_index == 0 ? (BRCM_LOG_BUFFER_MAX_ENTRIES - 1) : (*brcm_log_index - 1);
		brcm_log_buffer[index].cpu      = raw_smp_processor_id();
#if defined(CONFIG_BCM617xx_LOGGER_TIME_IS_MCTU)
		if (brcm_log_is_mctu_active)
		{
			PRC_CPU_WRITE(MCTU_UPDATE_REGS,0x1);
			brcm_log_buffer[index].ts.timestamp_high = brcm_logger_get_timestamp_high();
			brcm_log_buffer[index].ts.timestamp_low  = brcm_logger_get_timestamp_low();
		}
		else
		{
			brcm_log_buffer[index].ts.timestamp_high = 0;
			brcm_log_buffer[index].ts.timestamp_low = 0;
		}
#elif defined(CONFIG_BCM617xx_LOGGER_TIME_IS_UTC)
		brcm_read_utc(&(brcm_log_buffer[index].utc));
#else // use the MIPS C0_Count reg.
		brcm_log_buffer[index].c0_count = read_c0_count();
#endif
		brcm_log_buffer[index].counter  = brcm_log_counter++;
		raw_spin_unlock_irqrestore(&logger_counter_lock, flags);

		brcm_log_buffer[index].event    = event;
		brcm_log_buffer[index].payload  = payload;
		brcm_log_buffer[index].file     = file;
		brcm_log_buffer[index].line     = line;
	}

}

#undef EXTERN
#endif /*__KERNEL__*/

typedef struct {
	const char *file;
	int line;
} logger_user_log_t;

#endif
