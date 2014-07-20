#ifndef FLE_DRIVER_H
#define FLE_DRIVER_H


#ifdef __KERNEL__
#define U32 u32
#define U16 u16
#else
#define U32 unsigned long
#define U16 unsigned short
#endif

#define L1_TO_DSP_MSG    					0
#define L1_TO_DSP_MULTIPLE_MSG		1
#define FLE_CONFIGURE_QUEUES 			2
#define FLE_GET_STATS							3	 
#define	FLE_GET_MCTU							4
#define	FLE_START									5
#define FLE_GET_LOG								6	 
#define FLE_WAIT_FOR_TTI					7
#define FLE_START_LTE							8		
#define FLE_TICK_MQ							  9		
	


#define FLE_DEBUG_LEVEL_NONE      0
#define FLE_DEBUG_LEVEL_CRITICAL  1
#define FLE_DEBUG_LEVEL_NORMAL    2
#define FLE_DEBUG_LEVEL_VERBOSE   3

#define	DSP_WORD_SIZE							4

typedef struct {
	int 						ms;
	int							mq;
	unsigned short	msg_code;
} fle_tick_mq_t;

#define  FLE_1MS_TICK							0
#define  FLE_2MS_TICK							1

typedef struct {
  void  *source;
  void  *target;
} fle_mem_transac_t;

typedef struct {                                                                                                  
     U32          mfc;
     U32          mcc;
} fle_mctu_t;

typedef struct {
  unsigned long 		key;
  int	        			quid;
  unsigned short	 	min_cmd;
  unsigned short 		max_cmd;
} queue_to_cmd_t;


#define					MAX_FLE_LOG_STR			200
#define					FLE_LOG_MAX_IDX			10000

#define					FLE_MODE_DUAL				1
#define					FLE_MODE_3G_LTE			2


#ifdef __KERNEL__

typedef struct {                                                                                                  
     U32				mfc;
     U32				mcc;
     U32				mslc;
     U32				tick;
     U32				debug_counter;

} prc_1ms_ind_t;

typedef struct {
   long								mtype;
   PRC_DSP_MSG_HEADER	header;
   prc_1ms_ind_t			payload;
} one_ms_tick_msg_t;





/* TODO: move this to one of the arch headers once they are cleaned up */
/*      ------------------------------------------------------------------------------------
*      |                           Control Area                                                                                   |
*      |              (6*32bits words)                                                                                        |
*      | 1. L1 write control word (L1->DSP messages)                                             |
*      | 2. L1 DSP read control word (DSP->L1 messages)                                     |
*      | 3. L1 ready Flag
*      | 4. DSP write control word (DSP->L1 messages)                                         |
*      | 5. DSP read control word (L1->DSP messages)                                          |
*      | 6. DSP ready Flag                                                                                                    |
*      |-------------------------------------------------------------------------------- -|
*      |                     DSP -> L1 messages Area                                                                |
*      |                       (256*32bits words)                                                                         |
*      |---------------------------------------------------------------------------------|
*      |                     L1 -> DSP messages Area                                                               |
*      |                       (1190*32bits words)                                                                      |
*      |---------------------------------------------------------------------------------|
*      |                     General Parameters Area                                                             |
*      |( (50 - "control area size" - "UBOOT area size") = 44*32bits words ) |
*      |-------------------------------------------------------------------------------- |
*      |                       UBOOT Interface Area                                                                  |
*      |                         (6*32bits words)                                                                           |
*      |---------------------------------------------------------------------------------|
*/




#define DSP_CONTROL_START					0xBE054000

//L1 - DSP Mailbox General Definitions:
//--------------------------------------
#define L1_DSP_MAILBOX_TOTAL_SIZE           (1536)    //size in 32bits words
#define UBOOT_AREA_SIZE                     (6)       //size in 32bits words
#define FPLOG_DSP_DUMP_CONTROL_AREA_SIZE    (26)      //size in 32bits words
#define MISS_TICK_COUNTERS_AREA_SIZE        (4)       //size in 32bits words

typedef union {
    U32		    controlWord;
    struct      {
                    U16  offset:16;          // offset in the appropriate messages area servers as the read or write messages offset depends on the context used
                    U16  numOfMessages:14;   // number of messages sent
                    U16  moreFlag:1;         // Flag that indicates that the other side has messages to send but has no more free room left in the buffer
                    U16  unused:1;
                };
} l1_dsp_control_word_t;

typedef struct {
                    l1_dsp_control_word_t write;
                    l1_dsp_control_word_t read;
                    U32 readyInd;
} l1_dsp_control_t;

typedef struct {
                    l1_dsp_control_t   L1Control;
                    l1_dsp_control_t   DspControl;
} l1_dsp_control_area_t;

typedef union {
                 U32 header;
                 struct {
                          U16 opcode;
                          U16 length;
                 };
}l1_dsp_msg_header_t;

#define L1_DSP_CONTROL_AREA_SIZE        ((sizeof(L1_DSP_CONTROL_AREA_STRUCT))/sizeof(uint32))    //size in 32bits words
#define L1_DSP_GENERAL_PARAMS_AREA_SIZE ((L1_DSP_MAILBOX_TOTAL_SIZE) - (UBOOT_AREA_SIZE) - (FPLOG_DSP_DUMP_CONTROL_AREA_SIZE) - (MISS_TICK_COUNTERS_AREA_SIZE) \
                                            - ((L1_TO_DSP_MSG_BUFFER_SIZE) + (DSP_TO_L1_MSG_BUFFER_SIZE) + (L1_DSP_CONTROL_AREA_SIZE)))




#define L1_DSP_WRITE_OFFSET							mailbox->controlArea.L1Control.write.offset
#define L1_DSP_READ_OFFSET							mailbox->controlArea.DspControl.read.offset
#define L1_DSP_NUM_MSGS									mailbox->controlArea.L1Control.write.numOfMessages

#define DSP_L1_READ_OFFSET							mailbox->controlArea.L1Control.read.offset
#define DSP_L1_WRITE_OFFSET							mailbox->controlArea.DspControl.write.offset
#define DSP_L1_NUM_MSGS_READ_BY_L1			mailbox->controlArea.L1Control.read.numOfMessages
#define DSP_L1_NUM_MSGS_WRITTEN_BY_DSP	mailbox->controlArea.DspControl.write.numOfMessages
#define DSP_L1_DSP_MORE_FLAG_IS_SET		  mailbox->controlArea.DspControl.write.moreFlag


#define L1_DSP_NULL_MSG_HEADER				0x0000FFFF
#define DSP_DSP_L1_MSG_BUF_SIZE				256UL
#define DSP_L1_DSP_MSG_BUF_SIZE				1190UL 

typedef struct {
   l1_dsp_control_area_t   controlArea;
   U32                     DspToL1cMsgBuffer[DSP_DSP_L1_MSG_BUF_SIZE];
   U32                     L1ToDspMsgBuffer[DSP_L1_DSP_MSG_BUF_SIZE];
} l1_dsp_mailbox_t;


typedef struct {
	void			*ptr;
	int				len;
} multi_l1_to_dsp_msg_t;


#define MAX_DSP_TO_L1_MSG		4096

/* structre definitions for messages that are sent from the FLE driver to the L1 application */
typedef struct {
    long				mtype;
    char				mtext[MAX_DSP_TO_L1_MSG];
 } queue_buf_t;





#define	FLE_RING_BUFFER_SIZE   4096U
/* this structure contains all the data required to manage the buffer that is used to handle long messages */


typedef struct {
	unsigned short		buffer[FLE_RING_BUFFER_SIZE];
	unsigned short		in_idx;
	unsigned short		out_idx;
	unsigned short		messages_to_send;
	unsigned short		bytes_to_send;
	spinlock_t				lock;
} fle_ring_buffer_t;

typedef struct {
   u64	num_of_tti_ints                ;
   u64	msgs_received_from_l1          ;
   u64	msgs_sent_to_dsp               ;
   u64	msgs_received_from_dsp         ;
   u32	 send_two_ms_tick_msg           ;
   u32	fle_driver_enable_read_from_dsp;
   u32	fle_enable_send_to_dsp         ;
   u32	fle_enable_send_int_to_dsp     ;
} fle_stats_t;


#define	KFIFO_FIFO_SIZE								32

#define MIN(a,b) ((a)<(b))?(a):(b)


#define TTI_INTERRUPT_EVENT						0
#define DSP_MSG_INTERRUPT_EVENT				1
#define	DSP_MSG_ACK_EVENT							2
#define MAX_FLE_QUEUES								15



typedef struct {
  struct			list_head msg_list;
  u32		num_of_msgs;
  u32		bytes;   
} l1_messages_list_t;

#define MAX_L1_TO_DSP_MSG_SIZE			1024
#define MAX_L1_TO_DSP_MSG_NUM				50


#ifdef __FLE_DRIVER__
#define EXTERN
#else
#define EXTERN extern
#endif
void   fle_call_tti_callbacks(void);
static inline	int 		fifo_add_msgs(void *user_ptr,int num);
int										wait_for_dsp(void);
static inline					multi_l1_to_dsp_msg_t* 	fifo_peek(void);
static inline	void 		fifo_skip(void);
static inline	int 		fifo_return_count(void);
static inline	void		get_mctu(prc_1ms_ind_t *ptr);
void									print_control_regs(char *msg);
static inline	void		fle_zero_l1c_dsp_write_offset(void);
static inline	void		fle_set_l1c_dsp_control_word(u16 offset,U16 num,U16 more) ;
static inline	void		fle_set_dsp_l1c_control_word(u16 offset,U16 num,U16 more) ;
static inline	void		fle_send_dummy_message(u16 *write);
static inline	int			fle_get_msg_from_user_space(void *dst,void *src,int len);
static inline	void		fle_send_msg_to_mailbox(u16 *write, void* src, int len,U16 *num_msgs,U16 length);
int										printk_queues(char *page, char **start, off_t off,int count, int *eof,void *data);
void									update_gloabl_queue_list(queue_to_cmd_t *temp,int num);
static inline	int			process_incoming_message(void);
static inline	int			fle_send_l1_msgs(void);
static int						fle_driver_cmd_demux(unsigned long cmd, unsigned long arg,void *arg1);
void									send_dsp_message(void *buf,unsigned short len);
static int						dsp_msg_kthread(void *data);
static irqreturn_t		fle_driver_dsp_msg_acknowledge(int irq, void *dev_id, struct pt_regs *regs);
static irqreturn_t		fle_driver_dsp_msg_arrived(int irq, void *dev_id, struct pt_regs *regs);
static irqreturn_t		fle_driver_tti_tick_handler(int irq, void *dev_id, struct pt_regs *regs);
int										register_interrupts(void);
static int __init			fle_driver_init_module (void);
static void __exit		fle_driver_cleanup_module (void);
void 									process_1ms_3g_interface(void);
void 									process_1ms_lte_interface(void);
void 									send_dsp_message(void *buf,unsigned short len);
void 									send_dsp_message_lte(void *buf,unsigned short len);





#undef EXTERN
#endif /* __KERNEL__ */
#endif 

