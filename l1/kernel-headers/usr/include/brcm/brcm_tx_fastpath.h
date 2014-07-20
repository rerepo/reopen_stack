#ifndef BRCM_FAST_TX_H
#define BRCM_FAST_TX_H




#define			TX_FPATH_MAGIC						0xCA1234FE
#define			TX_FPATH_MAGIC_1					0xCA1234FA
#define			TX_FPATH_MAGIC_2					0xCA1234FB

#define 		BRCM_TX_FPATH_SINGLE 		  0x0
#define 		BRCM_TX_FPATH_MULTI				0x1
#define 		BRCM_TX_FPATH_LAST   			0x2
#define 		BRCM_TX_FPATH_FIRST   		0x4

#define 		BRCM_TX_PACKT_SEPERATOR   0xFFCAFEFF


#define 	  BRCM_TX_OPTION_DSCP_MASK  0xFF
typedef struct 
{
	unsigned long		magic;
	unsigned long		operation;
	struct iovec  	*iov;
  unsigned short	  dscp;
} tx_fpath_ctl_t;



#ifdef __KERNEL__
#define TX_FP_START					 					0
#define TX_FP_GET_USER_PARAMS 				1
#define TX_FP_GOLDEN_PRE_IPSEC				2	
#define TX_FP_GOLDEN_POST_IPSEC				3	
#define TX_FP_GET_STATE								4	
#define TX_FP_GET_MSG_SYS_ENTRY  			5
#define TX_FP_PROCESS_ACC							6
#define TX_FP_ADD_PACKET							7
#define TX_FP_ADD_LAST_PACKET					8
#define MAX_FRAGS_IN_PACKET 					10

#define TX_FP_MAX_N										50
#define TX_FP_NUM_TO_ACC   						20 

typedef enum {
  TX_FP_STATE_INIT				=	0,
	TX_FP_STATE_FIRST_PACKET,
	TX_FP_STATE_INIT_DONE,
	TX_FP_STATE_ACC_DONE,
	
} tx_fp_states_t;



#define   TX_FP_RC_FIRST_PACKET	  		0
#define   TX_FP_RC_INIT_DONE		  		1
#define   TX_FP_RC_DONE		       		 	2

extern int (*prc_ipsec_tx_hook)(int cmd ,struct iovec *user_iovec, struct sk_buff* skb, int param1,unsigned short dscp);
#endif

#endif