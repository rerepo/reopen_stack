#ifndef BRCM_SYSCALLS_H
#define BRCM_SYSCALLS_H
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include <linux/version.h>

#include "brcm_l1_common_interface.h"
#include "brcm_frame_cap.h"
#include "brcm_drivers.h"
#include "brcm_logger.h"
#include "brcm_mmap.h"
#include "brcm_dma.h"
#include "brcm_dsp.h"
#include "brcm_FSM.h"
#include "fle-driver.h"
#include "brcm_cpu_ipc.h"
#include "brcm_turbo.h"
#include "brcm_mmap_ipc.h"
#include "brcm_f8.h"
#include "brcm_sniffer.h"
#include "brcm_rsa.h"
#include "brcm_fastsock.h"
#include "brcm_tx_fastpath.h"
#include "brcm_wd.h"
#include "brcm_AES.h"

/* Base IDs for shared indices of MMAP/SHARED/IPC drivers */
#define USER_SHARED_ID_BASE		5
#define USER_MMAP_ID_BASE		5
#define USER_IPC_ID_BASE		FIRST_USER_PORT_ID

#undef __NR_brcm_hook 
//#define __NR_brcm_hook  0x10EA
#if LINUX_VERSION_CODE <= KERNEL_VERSION(3,0,1)
#define __NR_brcm_hook  0x10F8 /* PAL */
#else
#define __NR_brcm_hook  0x10FB /* PAL */
#endif


/*********************************************/
/*          sniffer driver syscalls          */
/*********************************************/
#define brcm_sniffer_init(sniffer_params)     	   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_SNIFFER,SNIFFER_INIT),0,(void*)(sniffer_params))



/*********************************************/
/*          CPU-IPC driver syscalls          */
/*********************************************/
#define brcm_ipc_release(port)			   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_UNBLOCK_PORT),(port),NULL)
#define brcm_ipc_open_port(port, size)     	   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_OPEN_PORT),(port),(void*)size)
#define brcm_ipc_close_port(port)          syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_CLOSE_PORT),(port),NULL)

static __inline int brcm_ipc_send_multi(int port, struct iovec *iov, int iov_len, int flags)
{
	mcpu_ipc_msg tx_ipc_msg;

	tx_ipc_msg.port = port;
	tx_ipc_msg.size = iov_len;
	tx_ipc_msg.pPayload = (void*)iov;
	tx_ipc_msg.flags = flags;
	
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_SEND_MULTI),sizeof(mcpu_ipc_msg),(void*)&tx_ipc_msg);
}
static __inline int brcm_ipc_send_msg(int port, void* msg, int len, int flags)
{
	mcpu_ipc_msg tx_ipc_msg;

	tx_ipc_msg.port = port;
	tx_ipc_msg.size = len;
	tx_ipc_msg.pPayload = msg;
	tx_ipc_msg.flags = flags;
	
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_SEND_MSG),sizeof(mcpu_ipc_msg),(void*)&tx_ipc_msg);
}

static __inline int brcm_ipc_recv_multi(int port, struct iovec *iov, int iov_len, int flags)
{
	int rc;
	mcpu_ipc_msg rx_ipc_msg;

	rx_ipc_msg.port = port;
	rx_ipc_msg.size = iov_len;
	rx_ipc_msg.pPayload = (void*)iov;
	rx_ipc_msg.flags = flags;

	/* Handle cases where we try to debug the application and get an interrupt signal */
	do {
		rc = syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_RECV_MULTI),sizeof(mcpu_ipc_msg),(void*)&rx_ipc_msg);
	} while (errno == EINTR);

	return rc;
}
static __inline int brcm_ipc_recv_msg(int port, void* msg, int len, int flags)
{
	int rc;
	mcpu_ipc_msg rx_ipc_msg;

	rx_ipc_msg.port = port;
	rx_ipc_msg.size = len;
	rx_ipc_msg.pPayload = msg;
	rx_ipc_msg.flags = flags;

	do {
		rc = syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_CPU_IPC,IPC_RECV_MSG),sizeof(mcpu_ipc_msg),(void*)&rx_ipc_msg);
	} while (errno == EINTR);

	return rc;
}

static __inline int mcpu_open_port(int port_id, int size)
{
	return brcm_ipc_open_port(port_id, size);
}

static __inline int mcpu_close_port(int port_id)
{
	return brcm_ipc_close_port(port_id);
}

static __inline int mcpu_send_message(int port_id, void *message, int msg_len, int flag)
{
	return brcm_ipc_send_msg(port_id, message, msg_len, flag);
}

static __inline int mcpu_recieve_message(int port_id, void *message, int max_len, int flag)
{
	return brcm_ipc_recv_msg(port_id, message, max_len, flag);
}

static __inline int mcpu_send_multiple_messages(int port_id, struct iovec *iov,  int iov_len, int flag) 
{
	return brcm_ipc_send_multi(port_id, iov, iov_len, flag);
}

static __inline int mcpu_recieve_multiple_message(int port_id, struct iovec *iov,  int iov_len,  int flag)
{
        return brcm_ipc_recv_multi(port_id, iov, iov_len, flag);
}


/*********************************************/
/*          FLE driver syscalls              */
/*********************************************/
#define brcm_fle_configure_queues(ptr,len)				syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FLE,FLE_CONFIGURE_QUEUES),(len),(ptr))
#define brcm_fle_send_multiple_dsp_msgs(ptr,len)	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FLE,L1_TO_DSP_MULTIPLE_MSG),(len),(ptr))
#define brcm_fle_start_lte(address,size)					syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FLE,FLE_START_LTE),(address),(size))
#define brcm_fle_start()													syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FLE,FLE_START),0,NULL)
#define brcm_fle_wait_for_tti()				  						syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FLE,FLE_WAIT_FOR_TTI),0,NULL)
static __inline int brcm_lte_counters(unsigned long *frame, unsigned long  *frame_chip_count)
{
	fle_mctu_t		fle_mctu;
	int				ret;
	ret = syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FLE,FLE_GET_MCTU),0,(&fle_mctu));
	if(!ret)
	{
		*frame = fle_mctu.mfc;
		*frame_chip_count = fle_mctu.mcc;
	}
	return ret;
}

/*********************************************/
/*            DMA driver syscalls            */
/*********************************************/
static __inline int brcm_dma_operation(unsigned long flags,int idx,int q_id,PRC_DMA_COPY *src)
{

	userspace_dma_request_t		request;

	request.flags	= flags;
	request.index	= idx;
	request.q_id	= q_id;
	request.copy_list	= src;
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DMA,DMA_MULTI),0,(&request));
}

/*********************************************/
/*            DSP driver syscalls             */
/*********************************************/
#define brcm_dsp_load()					   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_LOAD),0,NULL)
static __inline int brcm_dsp_read(dsp_read_write_t *params)
{

        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_READ),0,(void *)(params));
}
static __inline int brcm_dsp_mem_test_1(unsigned long s_addr, unsigned long e_addr, long mask)
{
        dsp_read_write_t params;
        params.addr = s_addr;
        params.data = e_addr;
        params.type = mask;
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_MEM_TEST_1),0,(void*)(&params));
}


static __inline int brcm_dsp_mem_test(unsigned long s_addr, unsigned long e_addr, long mask)
{
        dsp_read_write_t params;
        params.addr = s_addr;
        params.data = e_addr;
        params.type = mask;
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_MEM_TEST),0,(void*)(&params));
}


static __inline int brcm_dsp_write(unsigned long addr, unsigned long data, long type)
{
        dsp_read_write_t params;
        params.addr = addr;
        params.data = data;
        params.type = type;
		
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_WRITE),0,(void*)(&params));
}


#define brcm_cpu_write(addr,val)		   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,CPU_WRITE),(addr),(void *)(val))
#define brcm_cpu_read(addr,val)			   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,CPU_READ),(addr),val)
#define brcm_dsp_compare(val)			   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_COMPARE),0,(void *)(val))

#define brcm_utc_read(ptr)				   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,UTC_READ),0,(void*)(ptr))
#define brcm_multicopy_physical(ptr)       syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_MULTIPLE_READ_WRITE),0,(void*)(ptr))
#define brcm_get_cpu_stats(stat,ptr)	   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_GET_CPU_STAT),(stat),(void*)(ptr))
#define brcm_get_cpu_stats_smp(ptr1,ptr)	   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_GET_CPU_STAT_SMP),(void*)ptr1,(void*)(ptr))
#define brcm_afc_dac_init()				   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,AFC_DAC_INIT),0,NULL)
#define brcm_utc_raw_read(ptr)           syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,UTC_RAW_READ),0,(void*)(ptr))


static __inline int brcm_time_stamp(unsigned long *sfn,unsigned long  *chip,unsigned long *utc_sec,unsigned long *utc_usec)
{
	
	prc_timestamp_t		tmp;
	int					ret;
	
	ret = syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,UTC_MFC_READ),0,(void *)&tmp);
	if(ret==0) 
	{
		*sfn = tmp.sfn;
		*chip = tmp.chip;
		*utc_sec =  tmp.sec;
		*utc_usec = tmp.usec;
	}
	return ret;
}


static __inline int  brcm_afc_dac(unsigned short type, unsigned long offset)
{
   afc_dac_t	afc_dac;
   afc_dac.type   = type;
   afc_dac.base   = 0;
   afc_dac.offset = offset;
   return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,AFC_DAC),0,(void*)(&afc_dac));
}

static __inline int  brcm_write_physical(void *virt_src,void *phys_dst, unsigned long len)
{ 
  fle_mem_transac_t mem_trans;
  mem_trans.source = virt_src; 
  mem_trans.target = phys_dst; 
  return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_WRITE_PHYSICAL)  ,len,&mem_trans);
}
static __inline__ int brcm_read_physical(void *virt_src,void *phys_dst, unsigned long len) 
{ 
  fle_mem_transac_t mem_trans;
  mem_trans.source = virt_src; 
  mem_trans.target = phys_dst; 
  return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_DSP,DSP_READ_PHYSICAL)   ,(len),&mem_trans);
}

/*********************************************/
/*        Logger driver syscalls             */
/*********************************************/
#define brcm_logger_reset_utc()	      			syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,START_UTC),0,NULL)
#define brcm_logger_get_index(ptr)	  			syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_INDEX),0,(void *)(ptr))
#define brcm_logger_get_index_other_cpu(ptr)	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_INDEX),1,(void *)(ptr))
#define brcm_logger_start_log()	      			syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,START_LOG),0,NULL)
#define brcm_logger_stop_log(ptr)	      		syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,STOP_LOG),0,(ptr))
#define brcm_logger_stop_log_other_cpu(ptr)	    syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,STOP_LOG),1,(ptr))
#define brcm_logger_get_cpu_freq(ptr)  			syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_CPU_FREQ),0,(void *)(ptr))
#define brcm_logger_get_count(ptr)				syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_CPU_COUNT),0,(void *)(ptr))


static __inline void  brcm_logger_get_utc(brcm_utc_t *utc)
{ 
  syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_UTC)  ,0,(void *)utc);
}
#define brcm_logger_log_function(ptr) brcm_logger_log_function_int((void *)ptr, __FILE__, __LINE__)

static __inline int brcm_logger_log_function_int(void *ptr, const char *file, int line)
{
	logger_user_log_t log_struct;
	log_struct.file = file;
	log_struct.line = line;
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,LOG_FUNCTION),ptr,(void *)&log_struct);
}

static __inline void brcm_logger_print_all_cpu_free_counters(void)
{
	static unsigned int sleepcnt[2] = {0, 0};
	static unsigned int freecnt[2]  = {0, 0};
	static unsigned int waitcnt[2]  = {0, 0};
	static unsigned int waitxcnt[2]  = {0, 0};
	static unsigned int current = 0;
	unsigned long cpu_freq;
	unsigned int cntdiff;
	unsigned int sleepdiff;
	unsigned int waitdiff;
	unsigned int waitxdiff;
	unsigned int free_var;

	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_COUNT),0,(void *)&freecnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_SLEEP),0,(void *)&sleepcnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_WAIT),0,(void *)&waitcnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_WAITX),0,(void *)&waitxcnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_CPU_FREQ),0,(void *)&cpu_freq);

	//Free
	if(freecnt[current] < freecnt[! current])
	{
		cntdiff = 0xffffffff - (freecnt[! current]);
		cntdiff += freecnt[current];
	}
	else
	{
		cntdiff = freecnt[current] - (freecnt[! current]);
	}

	//Sleep
	if(sleepcnt[current] < sleepcnt[! current])
	{
		sleepdiff = 0xffffffff - (sleepcnt[! current]);
		sleepdiff += sleepcnt[current];
	}
	else
	{
		sleepdiff = sleepcnt[current] - (sleepcnt[! current]);
	}

	//Wait
	if(waitcnt[current] < waitcnt[! current])
	{
		waitdiff = 0xffffffff - (waitcnt[! current]);
		waitdiff += waitcnt[current];
	}
	else
	{
		waitdiff = waitcnt[current] - (waitcnt[! current]);
	}
	//WaitX
	if(waitxcnt[current] < waitxcnt[! current])
	{
		waitxdiff = 0xffffffff - (waitxcnt[! current]);
		waitxdiff += waitxcnt[current];
	}
	else
	{
		waitxdiff = waitxcnt[current] - (waitxcnt[! current]);
	}

	printf("\n1st Read:\n");
	printf("*********\n");
	printf("	Count reg (C0 Reg  9 Sel 0): 0x%08x\n", freecnt [! current]);
	printf("	Sleep reg (C0 Reg 22 Sel 7): 0x%08x\n", sleepcnt[! current]);
	printf("	Wait  reg (C0 Reg  9 Sel 7): 0x%08x\n", waitcnt [! current]);
	printf("	WaitX reg (C0 Reg  9 Sel 6): 0x%08x\n", waitxcnt[! current]);
	printf("\n1st Read:\n");
	printf("*********\n");
	printf("	Count reg (C0 Reg  9 Sel 0): 0x%08x\n", freecnt [current]);
	printf("	Sleep reg (C0 Reg 22 Sel 7): 0x%08x\n", sleepcnt[current]);
	printf("	Wait  reg (C0 Reg  9 Sel 7): 0x%08x\n", waitcnt [current]);
	printf("	WaitX reg (C0 Reg  9 Sel 6): 0x%08x\n", waitxcnt[current]);
	printf("\nCPU FREE:\n");
	printf("*********\n");
	free_var = (10000 * (float)((float)sleepdiff / (float)cntdiff));
	printf("CPU FREE both threads: %d.%02d \n", (free_var/100), (free_var%100));
	free_var = (10000 * (float)((float)waitdiff / (float)cntdiff));
	printf("CPU FREE this thread: %d.%02d \n", (free_var/100), (free_var%100));
	free_var = (10000 * (float)((float)waitxdiff / (float)cntdiff));
	printf("CPU FREE other thread: %d.%02d \n", (free_var/100), (free_var%100));
	printf("CPU frequency %ld.%02ld MHz \n", cpu_freq/1000000,
	       	(cpu_freq%1000000)*100/1000000);

	current = ! current;
}

static __inline void brcm_logger_calc_cpu_free(int print, unsigned int *complete, unsigned int *fraction)
{
	static unsigned int sleepcnt[2] = {0, 0};
	static unsigned int freecnt[2]  = {0, 0};
	static unsigned int current = 0;
	unsigned int cntdiff;
	unsigned int sleepdiff;
	unsigned int free_var;

	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_COUNT),0,(void *)&freecnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_SLEEP),0,(void *)&sleepcnt[current]);

	if(freecnt[current] < freecnt[! current])
	{
		cntdiff = 0xffffffff - (freecnt[! current]);
		cntdiff += freecnt[current];
	}
	else
	{
		cntdiff = freecnt[current] - (freecnt[! current]);
	}

	if(sleepcnt[current] < sleepcnt[! current])
	{
		sleepdiff = 0xffffffff - (sleepcnt[! current]);
		sleepdiff += sleepcnt[current];
	}
	else
	{
		sleepdiff = sleepcnt[current] - (sleepcnt[! current]);
	}

	if(print)
	{
		free_var = (10000 * (float)((float)sleepdiff / (float)cntdiff));
		*complete = (free_var/100);
		*fraction = (free_var%100);
		printf("CPU FREE Both Threads: %d.%02d \n", *complete, *fraction);
	}

	current = ! current;
}

static __inline void brcm_logger_calc_cpu_free_this_thread(int print, unsigned int *complete, unsigned int *fraction)
{
	static unsigned int sleepcnt[2] = {0, 0};
	static unsigned int freecnt[2]  = {0, 0};
	static unsigned int current = 0;
	unsigned int cntdiff;
	unsigned int sleepdiff;
	unsigned int free_var;

	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_COUNT),0,(void *)&freecnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_WAIT),0,(void *)&sleepcnt[current]);

	if(freecnt[current] < freecnt[! current])
	{
		cntdiff = 0xffffffff - (freecnt[! current]);
		cntdiff += freecnt[current];
	}
	else
	{
		cntdiff = freecnt[current] - (freecnt[! current]);
	}

	if(sleepcnt[current] < sleepcnt[! current])
	{
		sleepdiff = 0xffffffff - (sleepcnt[! current]);
		sleepdiff += sleepcnt[current];
	}
	else
	{
		sleepdiff = sleepcnt[current] - (sleepcnt[! current]);
	}

	if(print)
	{
		free_var = (10000 * (float)((float)sleepdiff / (float)cntdiff));
		*complete = (free_var/100);
		*fraction = (free_var%100);
		printf("CPU FREE This Thread: %d.%02d \n", *complete, *fraction);
	}

	current = ! current;	
}

static __inline void brcm_logger_calc_cpu_free_other_thread(int print, unsigned int *complete, unsigned int *fraction)
{
	static unsigned int sleepcnt[2] = {0, 0};
	static unsigned int freecnt[2]  = {0, 0};
	static unsigned int current = 0;
	unsigned int cntdiff;
	unsigned int sleepdiff;
	unsigned int free_var;

	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_COUNT),0,(void *)&freecnt[current]);
	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_LOGGER,GET_PERF_WAITX),0,(void *)&sleepcnt[current]);

	if(freecnt[current] < freecnt[! current])
	{
		cntdiff = 0xffffffff - (freecnt[! current]);
		cntdiff += freecnt[current];
	}
	else
	{
		cntdiff = freecnt[current] - (freecnt[! current]);
	}

	if(sleepcnt[current] < sleepcnt[! current])
	{
		sleepdiff = 0xffffffff - (sleepcnt[! current]);
		sleepdiff += sleepcnt[current];
	}
	else
	{
		sleepdiff = sleepcnt[current] - (sleepcnt[! current]);
	}

	if(print)
	{
		free_var = (10000 * (float)((float)sleepdiff / (float)cntdiff));
		*complete = (free_var/100);
		*fraction = (free_var%100);
		printf("CPU FREE Other Thread: %d.%02d \n", *complete, *fraction);
	}

	current = ! current;
}

/*********************************************/
/*            F8 driver syscalls             */
/*********************************************/

#define brcm_f8_read_status_1(set)		   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8,READ_STATUS),(set),NULL)
#define brcm_f8_setup_1(endian,reverse)  syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8,F8_SETUP),(endian),(void*)(reverse))


#define brcm_f8_read_status_2(set)		   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8_2,READ_STATUS),(set),NULL)
#define brcm_f8_setup_2(endian,reverse)  syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8_2,F8_SETUP),(endian),(void*)(reverse))


static __inline void brcm_f8_start_set(int idx,int set)
{
	if(idx == 1)
		 syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8,START_SET),set,NULL);
	else
	   syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8_2,START_SET),set,NULL);

}


static __inline int brcm_f8_cipher(int idx,int mode, brcm_cipher_params_t *cipher_params,int number_of_pdu, brcm_f8_data_t *pdu_list)
{
   
	brcm_cipher_t  cipher;
	cipher.mode = mode;
	memcpy(&cipher.config_params,cipher_params,sizeof(brcm_cipher_params_t));
	cipher.number_of_pdu = number_of_pdu;
  cipher.pdu_list = pdu_list;
	/*memcpy(&cipher.pdu_list,pdu_list,sizeof(brcm_f8_data_t));*/
	if(idx == 1)
		return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8,F8_CIPHER),0,(&cipher));
	else
		return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_F8_2,F8_CIPHER),0,(&cipher));
}


static __inline int brcm_f8_wait_for_set_ready(int idx,unsigned long set)
{
	int status_reg = 1;
	while(status_reg)
	{
		if(idx == 1)
			status_reg = brcm_f8_read_status_1(set);
		else
			status_reg = brcm_f8_read_status_2(set);
	}
	return 0;
}

static __inline  int brcm_f8_wait_for_set_ready_timeout(int idx,unsigned long set,int timeout)
{
	int status_reg = 1;
	int wait_counter = 0;
	while(status_reg && wait_counter < timeout) 
	{
		if(idx == 1)
			status_reg = brcm_f8_read_status_1(set);
		else
			status_reg = brcm_f8_read_status_2(set);
		if(status_reg)
		{
			sleep(1);
			wait_counter++;
		}	
	}
	return 0;
}




/*********************************************/
/*          mmap driver syscalls     */
/*********************************************/
#define brcm_mmap_shared_get_buf_size(idx, ptr)     	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_GET_BUFFER_SIZE),(idx),ptr)
#define brcm_mmap_shared_get_offset(idx, ptr)       	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_GET_BUFFER_OFFSET ),(idx),ptr)
#define brcm_mmap_shared_get_physical(idx, ptr)     	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_GET_BUFFER_PHYSICAL),(idx),ptr)
#define brcm_mmap_shared_get_virtual(idx, ptr)     		syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_GET_BUFFER_VIRTUAL),(idx),ptr)
#define brcm_mmap_shared_flush(addr, len, flags)		syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_FLUSH_CACHE),(addr),(void*)(len))
#define brcm_mmap_shared_invalidate(addr, len, flags)	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_INV_CACHED_BUFFER),(addr),(void*)(len))
#define brcm_mmap_shared_flush_multi(iov, iovitems, flags)		syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_FLUSH_CACHE_MULTI),(iovitems),(void*)(iov))
#define brcm_mmap_shared_invalidate_multi(iov, iovitems, flags)	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_INV_CACHED_BUFFER_MULTI),(iovitems),(void*)(iov))

#define brcm_mmap_ipc_get_buf_size			brcm_mmap_shared_get_buf_size
#define brcm_mmap_ipc_get_offset			brcm_mmap_shared_get_offset
#define brcm_mmap_ipc_get_physical			brcm_mmap_shared_get_physical
#define brcm_mmap_ipc_flush					brcm_mmap_shared_flush
#define brcm_mmap_ipc_invalidate			brcm_mmap_shared_invalidate

//use granularity of 0x1000 bytes at least for "len" (one page)
static __inline unsigned long brcm_mmap_shared_allocate_mem(unsigned long idx, unsigned long len, unsigned long cached)
{ 
	unsigned long rc;
	if(idx >= BRCM_MMAP_IPC_NUM_OF_INSTANCES)
	{
		printf("No such device instance IDx: %d\n",(unsigned int)idx);
		return -(ENODEV);
	}

   if(len & 0x00000fff)
   {
	   printf("Size is not page aligned\n");
	   return -(EINVAL);
   }

	if(cached)
		len |= 0x1;

	rc = syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP_IPC,MMAP_IPC_ALLOCATE_MEMORY),(idx),(len));

	return rc;
}

static __inline unsigned long brcm_mmap_ipc_allocate_mem(unsigned long idx, unsigned long len,unsigned long offset, unsigned long cached)
{
	return brcm_mmap_shared_allocate_mem(idx, len, cached);
}

//use granularity (both for "len" and "offset" of 0x1000 bytes at least)
static __inline unsigned long brcm_mmap_shared_init(unsigned long idx, unsigned long mem_to_alloc, unsigned long cached)
{ 
   int				fd;
   void				*mptr;
   long	            virt = 0;
   char				dev_name[128];
 
   virt = brcm_mmap_shared_allocate_mem(idx, mem_to_alloc, cached);
   if (virt <= 0) 
   {  
	   return 0xFFFFFFFF;
   }

	if(idx > 0)
		sprintf(dev_name,"/dev/brcm_mmap_shared_%d",(int)idx);
	else
		strcpy(dev_name,"/dev/brcm_mmap_shared");

   fd = open(dev_name, O_RDWR | O_SYNC);
   if( fd == -1) {
       printf("brcm_mmap_shared_init: open error for idx %d...\n", (int)idx);
       return 0xFFFFFFFF;
   }

 
   mptr = mmap((void*)virt, mem_to_alloc, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED | MAP_FIXED, fd, 0);
   if(mptr == MAP_FAILED) {
		printf("brcm_mmap_shared_init: mmap() failed for idx %d\n", (int)idx);
		return 0xFFFFFFFF;
   }
#ifdef VERBOSE
   printf("brcm_mmap_shared_init: mapped %lu bytes to ptr %p\n",mem_to_alloc,mptr);
#endif
   return (unsigned long)mptr;
}

static __inline unsigned long brcm_mmap_ipc_init(unsigned long idx, unsigned long virt,unsigned long offset,unsigned long mem_to_alloc, unsigned long cached)
{
	return brcm_mmap_shared_init(idx, mem_to_alloc, cached);
}

/*********************************************/
/*          mmap driver syscalls     */
/*********************************************/

#define brcm_mmap_get_buf_size(ptr,idx)     syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,GET_BUFFER_SIZE),(idx),(ptr))
#define brcm_mmap_get_offset(ptr,idx)       syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,GET_BUFFER_OFFSET ),(idx),(ptr))
#define brcm_mmap_get_physical(ptr,idx)     syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,GET_BUFFER_PHYSICAL),(idx),(ptr))
#define brcm_convert_uva_to_kva(arg)	    syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,UV_TO_K),(arg),NULL)
#define brcm_mmap_flush(addr, len, flags)	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,FLUSH_CACHED_BUFFER),(addr),(void*)(len))
#define brcm_mmap_invalidate(addr, len, flags)	syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,INV_CACHED_BUFFER),(addr),(void*)(len))


static __inline unsigned long brcm_mmap_allocate_mem_ext(unsigned long len,unsigned long idx, unsigned int cached)
{ 
	if(cached)
		return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,ALLOCATE_MEMORY),(len),(void*)(idx | 0x80000000));
	else
		return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_MMAP,ALLOCATE_MEMORY),(len),(void*)(idx));
}

static __inline unsigned long brcm_mmap_init_ext(unsigned long mem_to_alloc,unsigned long idx, unsigned int cached)
{ 

   char				dev_name[128];
   int				fd;
   unsigned long	size=0;
   void				*mptr;
   long int 		status = 0;
   
	if(idx > 0)
		sprintf(dev_name,"/dev/brcm_mmap_%d",(int)idx);
	else
		strcpy(dev_name,"/dev/brcm_mmap");

   status = brcm_mmap_allocate_mem_ext(mem_to_alloc, idx, cached);
   if (status != 0) 
   {
	   printf("brcm_mmap_allocate_mem failed\n");
	   return 0xFFFFFFFF;
   }
   fd = open(dev_name, O_RDWR | O_SYNC);
   if( fd == -1) {
       printf("open error...\n");
       return 0xFFFFFFFF;
   }

   brcm_mmap_get_buf_size(&size,idx);
   printf("Allocated size = %ld\n",size);
   mptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, fd, 0);
   if(mptr == MAP_FAILED) {
		printf("mmap() failed\n");
		return 0xFFFFFFFF;
   }
#ifdef VERBOSE
   printf("Mapped %lu bytes to ptr %p\n",size,mptr);
#endif
   return (unsigned long)mptr;
}

static __inline unsigned long brcm_mmap_allocate_mem(unsigned long len,unsigned long idx)
{
	return brcm_mmap_allocate_mem_ext(len,idx,0);
}
static __inline unsigned long brcm_mmap_init(unsigned long mem_to_alloc,unsigned long idx)
{
	return brcm_mmap_init_ext(mem_to_alloc,idx,0);
}


/*********************************************/
/* FSM Driver   syscalls                                                     */
/*********************************************/
static __inline unsigned long brcm_fsm_reload_fout()
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_RELOAD_FOUT),0,NULL);
}
static __inline unsigned long brcm_fsm_read_bit(unsigned long bit)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_READ_BIT),bit,NULL);
}
static __inline unsigned long brcm_fsm_read_all(brcm_fsm_params_t *fsm_params)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_READ_ALL),0,(void*)fsm_params);
}
static __inline unsigned long brcm_fsm_prog_bit(unsigned long bit)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_PROG_BIT),bit,NULL);
}
static __inline unsigned long brcm_fsm_prog_sec1(brcm_fsm_params_t *fsm_params)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_PROG_SEC1),0,(void*)fsm_params);
}
static __inline unsigned long brcm_fsm_prog_sec2(brcm_fsm_params_t *fsm_params)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_PROG_SEC2),0,(void*)fsm_params);
}
static __inline unsigned long brcm_fsm_prog_sec3(brcm_fsm_params_t *fsm_params)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_PROG_SEC3),0,(void*)fsm_params);
}
static __inline unsigned long brcm_fsm_prog_sec4(brcm_fsm_params_t *fsm_params)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FSM,FSM_PROG_SEC4),0,(void*)fsm_params);
}


/*********************************************/
/*        Turbo 3G/CDMA driver syscalls      */
/*********************************************/
static __inline int brcm_3g_hw_decode(percello_cb_t *cbDecode)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_TURBO,HW_BLOCK_3G),0,(void*)cbDecode);
}

static __inline int brcm_cdma_hw_decode(percello_cb_t *cbDecode)
{
        return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_TURBO_2,HW_BLOCK_CDMA2000),0,(void*)cbDecode);
}

/*********************************************/
/*            RSA driver syscalls            */
/*********************************************/
static __inline int brcm_rsa_hw_encrypt(rsa_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_RSA,RSA_ENCRYPT),0,(void*)params);
}

static __inline int brcm_rsa_hw_decrypt(rsa_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_RSA,RSA_DECRYPT),0,(void*)params);
}

static __inline int brcm_rsa_prog_key(rsa_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_RSA,RSA_SET_PRIVATE_KEY),0,(void*)params);
}


/*********************************************/
/*            Watchdog driver syscalls            */
/*********************************************/
static __inline int brcm_wd_kick_params(unsigned long tout)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_WD,WD_KICK_WITH_PARAMS),tout,NULL);
}

static __inline int brcm_wd_kick_def_max_params(void)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_WD,WD_KICK_MAX_PARAMS),15,NULL);
}

static __inline int brcm_wd_rearm(void)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_WD,WD_REARM),0,(void*)0);
}

static __inline int brcm_wd_set_tout(unsigned long tout)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_WD,WD_SET_TOUT),tout,(void*)0);
}

static __inline int brcm_wd_stop(void)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_WD,WD_STOP),0,(void*)0);
}

/*********************************************/
/*            FASTSOCK driver syscalls       */
/*********************************************/
static __inline int brcm_fastsock_close(int sock_id)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FASTSOCK,FASTSOCK_CLOSE),sock_id,(void*)NULL);
}

static __inline int brcm_fastsock_open(char *dest_ip,short port)
{
	fastsock_open_t 	params;
	unsigned long			u_dest_ip;
  unsigned char 		ipbytes[4];
  char 							*e,*s;
  char            	tmp[4];
  int 							count,j;
  int 							len;


  s = dest_ip;
  e = s;
  for(j = 0;j < 4; j++)
  {
  	for(count=0; count < 4;count++)
  	{
	 	  if( (*e=='.') || (*e=='\0') )
 	  	{
 	  		len = (int)e-(int)s;
	 	  	strncpy(tmp,s,len);
	 	  	tmp[len]='\0';
 	  		ipbytes[3-j]=atoi(tmp);
 	  		break;
 	  	}	
 	  	e++;
  	}
  	e++;
  	s = e;
  }
  u_dest_ip = (ipbytes[3]<<24|ipbytes[2]<<16|ipbytes[1]<<8|ipbytes[0]);
	params.port = port;
	params.dest_ip = u_dest_ip;
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FASTSOCK,FASTSOCK_OPEN),0,(void*)&params);
}


static __inline int brcm_fastsock_ioctl(unsigned short cmd,unsigned long param)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FASTSOCK,FASTSOCK_IOCTL),cmd,(void*)param);
}


static __inline int brcm_fastsock_init_memory_buffers(int memory_idx)
{
	fastsock_mem_init_t   mem_init;
	brcm_mmap_shared_get_virtual(memory_idx, &mem_init.virt_base);
	brcm_mmap_shared_get_physical(memory_idx, &mem_init.phys_base); 
	return brcm_fastsock_ioctl(FASTSOCK_IOCTL_MEM_INIT,(unsigned long)&mem_init);
}

static __inline int brcm_fastsock_add_elements_to_pool(unsigned int nElements, unsigned int  *arrElements)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FASTSOCK,FASTSOCK_ADD_MEM_CMD),nElements,(void*)arrElements);
}

static __inline int brcm_fastsock_rcv(int sock_id, skb_fifo_t *received, int max,int accumulation_period_in_ms)
{
	fastsock_rcv_t	tmp;
	tmp.received = received;
	tmp.max = max;
	tmp.accumulation_period_in_ms = accumulation_period_in_ms;
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_FASTSOCK,FASTSOCK_RECV),sock_id,(void*)&tmp);
}

/*********************************************/
/*			AES Driver syscalls              */
/*********************************************/
static __inline unsigned long brcm_aes_ecb(aes_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_AES,AES_ECB),0,(void*)params);
}

static __inline unsigned long brcm_aes_ecb_cpu(aes_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_AES,AES_ECB_CPU),0,(void*)params);
}

static __inline unsigned long brcm_aes_cbc(aes_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_AES,AES_CBC),0,(void*)params);
}

static __inline unsigned long brcm_aes_xcbc_mac(aes_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_AES,AES_XCBC_MAC),0,(void*)params);
}

static __inline unsigned long brcm_aes_start(aes_params_t *params)
{
	return syscall(__NR_brcm_hook,SET_SYSCALL_CMD(BRCM_DRIVER_AES,AES_START),0,(void*)params);
}

#endif

