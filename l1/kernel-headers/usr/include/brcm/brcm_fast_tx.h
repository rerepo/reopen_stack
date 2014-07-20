#ifndef BRCM_FAST_TX_H
#define BRCM_FAST_TX_H

#define TX_FP_START					 			0
#define TX_FP_GET_USER_PARAMS 		1
#define TX_FP_GOLDEN_PRE_IPSEC		2	
#define TX_FP_GOLDEN_POST_IPSEC		3	
#define TX_FP_GET_STATE						4	
#define TX_FP_GET_MSG_SYS_ENTRY   5
#define TX_FP_PROCESS_ACC					6
#define TX_FP_ADD_PACKET					7

#define TX_FP_MAX_N								50
#define TX_FP_NUM_TO_ACC   				10

typedef enum {
  TX_FP_STATE_INIT				=	0,
	TX_FP_STATE_FIRST_PACKET,
	TX_FP_STATE_INIT_DONE,
	TX_FP_STATE_ACC_DONE,
	
} tx_fp_states_t;

typedef struct
{
	u32 prot;
	u32 len;
	u32 skb_is_gso;
	u32 skb_gso_ok;
	u32 ip_summed;
	u32 total_len;
} tx_fpath_sent_packet_t;

#define SIZE_OF_REJ_ARRAY 200;




#define   TX_FP_RC_FIRST_PACKET	  0
#define   TX_FP_RC_INIT_DONE		  1
#define   TX_FP_RC_DONE		        2

extern int (*prc_ipsec_tx_hook)(int cmd , void *data, int param1);

#endif