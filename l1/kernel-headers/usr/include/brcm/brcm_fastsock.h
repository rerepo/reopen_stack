#ifndef BRCM_FASTSOCK_H
#define BRCM_FASTSOCK_H

#ifdef __KERNEL__
#include<asm/r4kcache.h>
#endif

#define FASTSOCK_FRAG_PACKET						0xcafecafe
#define FASTSOCK_BUFFER_SIZE						1500

#define FASTSOCK_ADD_MEM_CMD 						0
#define FASTSOCK_RECV										1      
#define FASTSOCK_OPEN        						2
#define FASTSOCK_CLOSE				 					3 
#define FASTSOCK_IOCTL				 					4

#define FASTSOCK_IOCTL_MEM_INIT					0

#define MAX_DST_IP_LEN 					 				16

#define KERNEL_CTX											0
#define USER_CTX												1

typedef struct {
	unsigned long    		dest_ip;
	unsigned long	 			port;
} fastsock_open_t;

typedef struct {
	unsigned long    		virt_base;
	unsigned long	 			phys_base;
} fastsock_mem_init_t;

typedef struct {
	unsigned short		frag_id;
  unsigned short		total_frags;
  void       				*packet;
  struct iovec 			data;
} skb_fifo_t;

typedef struct {
	int 								accumulation_period_in_ms;
	skb_fifo_t  				*received;
	int 								max;
} fastsock_rcv_t;	
	
	
#ifdef __KERNEL__
#define NUM_OF_MEM_ELEMENTS								10000
#define MAX_FIFO_ENTRY 										8192
#define SEARCH_KEY_IS_DEST_IP							0
#define SEARCH_KEY_IS_PORT								1
/* ***********************************************************************************************************************
 * FIFO related variables and functions. The network driver pushed entries into FIFO (1 at a time). User space socket call 
 * pops packets out (can be more than one at a time)
 * ************************************************************************************************************************/
typedef struct {
	u16 									  skb_fifo_in;    			  /* ethernet driver inserts at this location */
	u16 									  skb_fifo_out;   			  /* socket API "pops" from this location */
	spinlock_t						  skb_fifo_lock;  			  /* concurrency (ethernet driver, user space) lock per socket */
	wait_queue_head_t				wait_queue;     			  /* user space waits on this queue until data is ready */
	u16											skb_fifo_count; 			  /* how many packets waiting in the queue */ 
	u32											port; 									/* port to accelrate for this socket */
	u32 										dest_ip;								/* destination IP of socket */
	u16											search_key_is;					/* 0=port 1=dest_ip */
	u32											*search_key_ptr;				/* pointer to either dest_ip or search_key fields*/
	skb_fifo_t 							skb_fifo_buffer[MAX_FIFO_ENTRY]; /* Packet fifo for this socket */
	u16											ms_to_accumulate;				/* set in receive. decremented each tti. wake up when zero if data available */
	u16											max_to_receive;					/* max packets receiver is willing to recive. set in each receive call */
	u32											rx_bytes;               /* totoal RX bytes */     
	u16											receive_called;					/* Set when receiver is waiting for data. used for accumulation timer*/
	int											user_sock_id;								/* Identifier used by user space */					
} fastsock_socket_t;

typedef fastsock_socket_t * 							 fastsock_socket_ptr_t ;
/* Some macros for easy readable access */
#define 		SOCKET											fastsock_sockets_array[sock_idx]	
#define 		ZERO_ELEMENT								&SOCKET->skb_fifo_buffer[0]		
#define 		OUT_PTR											&SOCKET->skb_fifo_buffer[SOCKET->skb_fifo_out]		
#define 		IN_PTR											&SOCKET->skb_fifo_buffer[SOCKET->skb_fifo_in]		
#define 		OUT_IDX											SOCKET->skb_fifo_out
#define 		IN_IDX											SOCKET->skb_fifo_in	
#define     COUNT              		      SOCKET->skb_fifo_count
#define     PORT	              	      SOCKET->port
#define     DEST_IP	            	      SOCKET->dest_ip
#define     SEARCH_KEY_IS         			SOCKET->search_key_is
#define 		SERACH_KEY									*(SOCKET->search_key_ptr)
#define 		SERACH_KEY_PTR							SOCKET->search_key_ptr
#define  		WAITQ												SOCKET->wait_queue
#define			LOCK												&(SOCKET->skb_fifo_lock)
#define			ACCU_TIMER  								SOCKET->ms_to_accumulate
#define			MAX_TO_RCV  								SOCKET->max_to_receive
#define     RX_BYTES										SOCKET->rx_bytes
#define			RECIEVER_WAITING						SOCKET->receive_called
#define			USR_SOCK_ID									SOCKET->user_sock_id





typedef u32 (*fastsock_mem_cb_t)(void);
typedef int (*fastsock_action_cb_t)(void *buf, int len);
typedef int (*fastsock_memfree_cb_t)(u32 arg, u32 *arg1, u32 ctx);
typedef int (*fastsock_lookup_cb_t)(void *buf, unsigned int *fastsock_id);

#define MAX_NUM_OPEN_SOCKETS						5		

#define DATA_INCLUDE_IP_HEADERS					0
#define DATA_INCLUDE_UDP_HEADERS				1
#define DATA_INCLUDE_UDP_PAYLOAD				2

typedef struct {
	fastsock_action_cb_t    fastsock_action_cb;
	fastsock_mem_cb_t				fastsock_mem_cb;
	fastsock_memfree_cb_t   fastsock_memfree_cb;
	fastsock_lookup_cb_t    fastsock_lookup_cb;
} fastsock_register_callbacks_t;





static inline void flush_caches(u32 start, u32 end)
{
	//flush the 1st and last words of the buffer so shared cache lines will be in main memory before invalidating the buffer
	flush_dcache_line(start);
	flush_scache_line(start);

  flush_dcache_line(end);
	flush_scache_line(end);
				
	__asm__ __volatile__("sync"); 
	
	//invalidate the buffer so next cached access will bring fresh data
	for( ; start < end; start +=32)
	{
			invalidate_dcache_line(start);
			invalidate_scache_line(start);
	}	
}



#ifdef __FASTSOCK_DRV__
#define EXTERN 

static int 				fast_sock_driver_cmd_demux(unsigned long cmd, unsigned long arg,void *arg1);
static int  __init	 	fastsock_driver_init_module (void); 
static void __exit 		fastsock_driver_cleanup_module (void); 

#else
#define EXTERN extern
#endif

EXTERN 	int 				skb_socket_receive(int socket_id,void *dst,int max,int time_to_accumulate);
EXTERN 	void        skb_fifo_add(int sock_idx,void *packet, void *data,int len,int frag,int total_frag);
#endif

#endif