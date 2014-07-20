#ifndef PERCELLO_AES_H
#define PERCELLO_AES_H


#define	AES_ECB_CPU				0
#define	AES_ECB					1
#define AES_CBC					2
#define AES_CBC_CPU				3
#define AES_XCBC_MAC			4
#define AES_XCBC_MAC_CPU		5
#define	AES_START				6
#define	AES_DMA_PRINT_RES		7

#define AES_CMD_CBC_SET_KEY		3
#define AES_CMD_CBC_ENCRYPT		6
#define AES_CMD_CBC_DECRYPT		9

#ifndef AES_BLOCK_SIZE
#define AES_BLOCK_SIZE			16
#endif




#define AES_PREFIX								 0xBE4A0000

#define AES_DATA_BUFFER							 AES_PREFIX
#define AES_CONTROL_REG                          (AES_PREFIX+(0x7f80  << 2))   /* 22 bits */
#define AES_CONTROL_REG_MEM_MODE_DMA_128_M       0x0
#define AES_CONTROL_REG_MEM_MODE_DMA_1024_M      0x1
#define AES_CONTROL_REG_MEM_MODE_DMA_CPU2K_M     0x2

#define AES_CONTROL_REG_IPSEC_OP_SEL_ENCRYPT_F   0x0 				 
#define AES_CONTROL_REG_IPSEC_OP_SEL_DECRYPT_F   0x4 				 

#define AES_CONTROL_REG_IPSEC_MODE_ECB_M         0x0
#define AES_CONTROL_REG_IPSEC_MODE_CFB_M         0x8
#define AES_CONTROL_REG_IPSEC_MODE_CBC_M         0x10
#define AES_CONTROL_REG_IPSEC_MODE_CTR_M         0x18
#define AES_CONTROL_REG_IPSEC_MODE_XCBC_MAC_M    0x20 
#define AES_CONTROL_REG_IPSEC_MODE_XCBC_PRE_M    0x28
#define AES_CONTROL_REG_IPSEC_MODE_CCM_A_M       0x30
#define AES_CONTROL_REG_IPSEC_MODE_CCM_E_M       0x38
/*11:CTR-IV,  */
/*15:CCM-E-IV */

#define AES_CONTROL_REG_REV_SEL_OFF_F  		     0x0
#define AES_CONTROL_REG_REV_SEL_ON_F  		     0x80

#define AES_CONTROL_REG_END_SEL_B	  		     8
#define AES_CONTROL_REG__END_SEL__MASK           0x0000ff00   /* [15:8] */
#define SET_AES_CONTROL_REG_END_SEL(x)           ((x) << AES_CONTROL_REG_END_SEL_B) & AES_CONTROL_REG__END_SEL__MASK

#define AES_CONTROL_REG_KEY_128_M				 0x0
#define AES_CONTROL_REG_KEY_192_M				 0x10000
#define AES_CONTROL_REG_KEY_256_M				 0x20000


#define AES_CONTROL_REG_RUN_KEY_EXP_M	         0x0
#define AES_CONTROL_REG_USE_EXIST_KEY_EXP_M	     0x40000

#define AES_CONTROL_REG_CTR_SIZE_M				 0x80000

#define aes_control_reg__use_kexp__start_bit     18
#define aes_control_reg__use_kexp__mask          0xfffbffff   /* [18] */
#define aes_control_reg__ctr_size__start_bit     19
#define aes_control_reg__ctr_size__mask          0xffc7ffff   /* [21:19] */
#define AES_MESSAGE_SIZE_REG                     (AES_PREFIX+(0x7f81  << 2))   /* 32 bits */
#define AES_START_REG                            (AES_PREFIX+(0x7f82  << 2))   /* 0 bits */
#define aes_inp_data_ready                       (AES_PREFIX+(0x7f83  << 2))   /* 0 bits */
#define AES_OUT_DATA_EMPTY_REG                   (AES_PREFIX+(0x7f84  << 2))   /* 0 bits */
#define aes_halt                                 (AES_PREFIX+(0x7f85  << 2))   /* 0 bits */
#define aes_continue                             (AES_PREFIX+(0x7f86  << 2))   /* 0 bits */
#define aes_clear                                (AES_PREFIX+(0x7f87  << 2))   /* 0 bits */
#define aes_monitor                              (AES_PREFIX+(0x7f88  << 2))   /* 6 bits */
#define aes_start_ccmae                          (AES_PREFIX+(0x7f89  << 2))   /* 0 bits */
#define AES_IV_ENCRY_3_REG                       (AES_PREFIX+(0x7f90  << 2))   /* 32 bits */
#define AES_IV_ENCRY_2_REG                       (AES_PREFIX+(0x7f91  << 2))   /* 32 bits */
#define AES_IV_ENCRY_1_REG                       (AES_PREFIX+(0x7f92  << 2))   /* 32 bits */
#define AES_IV_ENCRY_0_REG                       (AES_PREFIX+(0x7f93  << 2))   /* 32 bits */
#define AES_IV_DECRY_3_REG                       (AES_PREFIX+(0x7f94  << 2))   /* 32 bits */
#define AES_IV_DECRY_2_REG                       (AES_PREFIX+(0x7f95  << 2))   /* 32 bits */
#define AES_IV_DECRY_1_REG                       (AES_PREFIX+(0x7f96  << 2))   /* 32 bits */
#define AES_IV_DECRY_0_REG                       (AES_PREFIX+(0x7f97  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_7_REG                      (AES_PREFIX+(0x7fb0  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_6_REG                      (AES_PREFIX+(0x7fb1  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_5_REG                      (AES_PREFIX+(0x7fb2  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_4_REG                      (AES_PREFIX+(0x7fb3  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_3_REG                      (AES_PREFIX+(0x7fb4  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_2_REG                      (AES_PREFIX+(0x7fb5  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_1_REG                      (AES_PREFIX+(0x7fb6  << 2))   /* 32 bits */
#define AES_KEY_ENCRY_0_REG                      (AES_PREFIX+(0x7fb7  << 2))   /* 32 bits */
#define AES_KEY_DECRY_7_REG                      (AES_PREFIX+(0x7fb8  << 2))   /* 32 bits */
#define AES_KEY_DECRY_6_REG                      (AES_PREFIX+(0x7fb9  << 2))   /* 32 bits */
#define AES_KEY_DECRY_5_REG                      (AES_PREFIX+(0x7fba  << 2))   /* 32 bits */
#define AES_KEY_DECRY_4_REG                      (AES_PREFIX+(0x7fbb  << 2))   /* 32 bits */
#define AES_KEY_DECRY_3_REG                      (AES_PREFIX+(0x7fbc  << 2))   /* 32 bits */
#define AES_KEY_DECRY_2_REG                      (AES_PREFIX+(0x7fbd  << 2))   /* 32 bits */
#define AES_KEY_DECRY_1_REG                      (AES_PREFIX+(0x7fbe  << 2))   /* 32 bits */
#define AES_KEY_DECRY_0_REG                      (AES_PREFIX+(0x7fbf  << 2))   /* 32 bits */



typedef enum {
	MEM_MODE_DMA_128		= AES_CONTROL_REG_MEM_MODE_DMA_128_M,
	MEM_MODE_DMA_1024		= AES_CONTROL_REG_MEM_MODE_DMA_1024_M, 
	MEM_MODE_DMA_CPU2K		= AES_CONTROL_REG_MEM_MODE_DMA_CPU2K_M
} aes_mem_mode_t;

typedef enum {
	IPSEC_OP_SEL_ENCRYPT	= AES_CONTROL_REG_IPSEC_OP_SEL_ENCRYPT_F,
	IPSEC_OP_SEL_DECRYPT	= AES_CONTROL_REG_IPSEC_OP_SEL_DECRYPT_F
} aes_ipsec_op_t;

typedef enum {
	IPSEC_MODE_ECB			= AES_CONTROL_REG_IPSEC_MODE_ECB_M     ,
	IPSEC_MODE_CFB			= AES_CONTROL_REG_IPSEC_MODE_CFB_M     ,
	IPSEC_MODE_CBC			= AES_CONTROL_REG_IPSEC_MODE_CBC_M     ,
	IPSEC_MODE_CTR			= AES_CONTROL_REG_IPSEC_MODE_CTR_M     ,
	IPSEC_MODE_XCBC_MAC		= AES_CONTROL_REG_IPSEC_MODE_XCBC_MAC_M,
	IPSEC_MODE_XCBC_PRE		= AES_CONTROL_REG_IPSEC_MODE_XCBC_PRE_M,
	IPSEC_MODE_CCM_A		= AES_CONTROL_REG_IPSEC_MODE_CCM_A_M   ,
	IPSEC_MODE_CCM_E		= AES_CONTROL_REG_IPSEC_MODE_CCM_E_M   
} aes_ipsec_mode_t;

typedef enum {
	REV_BIT_OFF				= AES_CONTROL_REG_REV_SEL_OFF_F,
	REV_BIT_ON				= AES_CONTROL_REG_REV_SEL_ON_F 
} aes_bit_rev_t;

typedef enum {
	KEY_128					= AES_CONTROL_REG_KEY_128_M,	
	KEY_192					= AES_CONTROL_REG_KEY_192_M,
	KEY_256					= AES_CONTROL_REG_KEY_256_M
} aes_key_size_t;

typedef enum {
	RUN_KEY_EXP		        = AES_CONTROL_REG_RUN_KEY_EXP_M,	   
	USE_EXIST_KEY_EXP		= AES_CONTROL_REG_USE_EXIST_KEY_EXP_M
} aes_run_key_t;

typedef struct {
	aes_mem_mode_t		aes_mem_mode;
	aes_ipsec_op_t		aes_ipsec_op;
	aes_ipsec_mode_t	aes_ipsec_mode;
	aes_bit_rev_t		aes_bit_rev;
	unsigned char		aes_reg_end;
	aes_key_size_t		aes_key_size; 
    aes_run_key_t		aes_run_key;
	unsigned char*		key;
	unsigned char*		iv;
	int					len;
	char				*plain_text;
	char				*cypher_text;
} aes_params_t;

typedef struct {
	char				name[20];
	int					idx;
} aes_data_t;

struct brcm_inout_params {
	unsigned char				*iv;
	unsigned char               *src;
	unsigned char				*dst;
};




#ifdef __AES_INTERNAL__
static int cbc_aes_decrypt(struct blkcipher_desc *desc,struct scatterlist *dst, struct scatterlist *src,unsigned int nbytes);
static int cbc_aes_encrypt(struct blkcipher_desc *desc,struct scatterlist *dst, struct scatterlist *src,unsigned int nbytes);
static int cbc_aes_set_key(struct crypto_tfm *tfm, const u8 *in_key,unsigned int key_len);
#endif


#endif

