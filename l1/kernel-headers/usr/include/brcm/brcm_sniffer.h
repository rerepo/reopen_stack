#ifndef SNIFFER_H
#define SNIFFER_H




#ifdef __KERNEL__
#define U32 u32
#define U16 u16
#else
#define U32 unsigned long
#define U16 unsigned short
#endif

#include "brcm_l1_common_interface.h"

#define SNIFFER_INIT				0

#define	SNIFFER_DSP_WORD_SIZE		sizeof(long)


typedef struct {
	U32		dsp_dpr_start;
	U32		dsp_dpr_end;
	U32		ddr_start;
	U32		ddr_end;
	U32 	ctrl_addr;
	U32		q_id;
} sniffer_params_t;



#ifdef __KERNEL__

typedef struct {
	U16		sniffer_flags;
	U16		chunk_offset;    
	U32		start_SFN;
	U32		start_Chip;
	U16		words_in_this_chunk;
	U16		DSP_mark;
	U32		L1C_mark;
} sniffer_control_block_t;
   

typedef struct {
   long											mtype;
   PRC_DSP_MSG_HEADER				header;
   sniffer_control_block_t	payload;
} sniffer_done_msg_t;





#ifdef __SNIFFER_DRIVER__
#define EXTERN
#else
#define EXTERN extern
#endif





#undef EXTERN
#endif /* __KERNEL__ */
#endif 

