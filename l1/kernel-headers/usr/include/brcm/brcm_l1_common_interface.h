#ifndef BRCM_L1_COMMON_INTERFACE_H
#define BRCM_L1_COMMON_INTERFACE_H

#ifdef __KERNEL__

typedef struct {
  unsigned short		cmd;
  unsigned short		len;
} l1_message_header_t;

/**************** FOR RSA Verify support *****************************/
/* copied from userland. under __KERNEL__ to avoid duplicate userland definitions because userland also includes this file */
#define  PRC_DSP_BASE                                                   (0x50)
#define	 PRC_DSP_DEBUG_PRINT__EVENT										(PRC_DSP_BASE + 0x43)
#define  PRC_DSP_L1B_RSA_SIGN_PRIVATE_REQ__EVENT                        (PRC_DSP_BASE + 0x63)
#define  PRC_DSP_L1B_RSA_SIGN_PRIVATE_CNF__EVENT                        (PRC_DSP_BASE + 0x64)
#define  PRC_KERNEL_LOG__EVENT											 0x201D

#define  PRC_DSP_DECODE_2048_PRIVATE_REQ__EVENT                         (PRC_DSP_BASE + 0x67)
#define  PRC_DSP_DECODE_2048_PRIVATE_CNF__EVENT                         (PRC_DSP_BASE + 0x68)
#define  PRC_DSP_SIGN_2048_PRIVATE_REQ__EVENT                           (PRC_DSP_BASE + 0x69)
#define  PRC_DSP_SIGN_2048_PRIVATE_CNF__EVENT                           (PRC_DSP_BASE + 0x6A)

#define PRC_DSP_SNIFFER_RECORD_IND__EVENT                               (PRC_DSP_BASE + 0x72)
#define  PRC_DMA_DONE_IND__EVENT										(0x2008)










/*
 * PRC_DSP_L1B_RSA_SIGN_PRIVATE_REQ:
 * Direction:L1->DSP
 * Description: Request to sign RSA with private key
 */
typedef struct {                                                                                                  
    unsigned short				msg_code;                                                                                     
    unsigned short				length;                                                                                       
} PRC_DSP_MSG_HEADER;   





typedef struct {                                                                                                  
       int               rc;   // 0 if success
       int               index;   // The index from the call.           
} PRC_DMA_DONE_IND;

typedef struct {
   long					mtype;
   PRC_DSP_MSG_HEADER   header;
   PRC_DMA_DONE_IND		payload;
} done_indication_t;




typedef struct {
    PRC_DSP_MSG_HEADER			header;
    unsigned short              data[64];
    unsigned short              public_key[64];
} PRC_DSP_L1B_RSA_SIGN_PRIVATE_REQ;


typedef struct {
    u16 buffer_to_sniffer_ready;  /* 0: Buffer ready  1:Last buffer ready  2:Periodic buffer ready */
    u16 end_of_last_chunk_in_DPR; /* Offset (from DDR start passed at init)  of the last chunk written */
    u32 start_sfn;                /* Start sfn of record */
    u32 start_sf_chip;            /* Start sf/chip of record */
    u16 num_of_samples;           /* Number of samples */
    u16 DSP_mark;                 /* DSP counter advances every recording intgerrupt */
    u32 L1C_mark;                 /* L1C counter advances every recording intgerrupt */
} PRC_DSP_SNIFFER_RECORD_IND_DATA;

typedef struct {
   long															mtype;
   PRC_DSP_MSG_HEADER   						header;
   PRC_DSP_SNIFFER_RECORD_IND_DATA	payload;
} sniffer_done_ind_t;



/*
 * PRC_DSP_L1B_RSA_SIGN_PRIVATE_CNF:
 * Direction:DSP->l1
 * Description: Confirms the Request to sign RSA with private key
 */
typedef struct {
    PRC_DSP_MSG_HEADER			header;
    unsigned short              status;  /* 0 measns success */
    unsigned short              signature[64];
} PRC_DSP_L1B_RSA_SIGN_PRIVATE_CNF;


typedef struct {
     PRC_DSP_MSG_HEADER  header;
    unsigned short       data[128];
    unsigned short       public_key[128];
} PRC_DSP_SIGN_2048_PRIVATE_REQ;

/*
 * PRC_DSP_SIGN_2048_PRIVATE_CNF__EVENT:
 * Direction:DSP->L1
 * Description: Confirms the sign request
 */

typedef struct {
     PRC_DSP_MSG_HEADER  header;
    unsigned short       status;	/* 0 measns success */
    unsigned short       signature[128];
} PRC_DSP_SIGN_2048_PRIVATE_CNF;


typedef struct {
     PRC_DSP_MSG_HEADER  header;
	 unsigned short      encoded_private_key[128];
} PRC_DSP_DECODE_2048_PRIVATE_REQ;






/**************** END OF RSA Verify support *****************************/



#endif /*__KERNEL__*/

#endif
