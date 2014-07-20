#ifndef BRCM_ACRYPT_SHA_H
#define BRCM_ACRYPT_SHA_H

#define	SHA1				  0
#define SHA1_HMAC			  1
#define SHA_PREFIX            0xBE480000

#define SHA_CMD_INIT          0x5
#define SHA_CMD_UPDATE	      0x7
#define SHA_CMD_FINAL         0x9

#define	SHA1_MEM_MODE_MASK	0x1
#define	SHA1_CPU_MODE		0x0
#define	SHA1_DMA_MODE		0x1

#define	SHA1_PARAM_MODE_MASK	0x2
#define	SHA1_SG_PARAMS			0x0
#define	SHA1_VOID_PTR_PARAMS	0x2


#define	SHA_DATA_BUFFER		  SHA_PREFIX

#define SHA_CONTROL_REG                              (SHA_PREFIX+(0x7f80 << 2))   // 16 bits
#define SHA_CONTROL_REG__MEM_MODE__START_BIT          0
#define SHA_CONTROL_REG_MEM_MODE_DMA_128_M			  0x0
#define SHA_CONTROL_REG_MEM_MODE_DMA_1024_M			  0x1
#define SHA_CONTROL_REG_MEM_MODE_DMA_CPU2K_M		  0x2

#define SHA_CONTROL_REG__IPSEC_OP_SEL__START_BIT      2
#define SHA_CONTROL_REG_IPSEC_OP_SEL_ENCRYPT_F		  0x0 				 
#define SHA_CONTROL_REG_IPSEC_OP_SEL_DECRYPT_F		  0x4 

#define SHA_CONTROL_REG__IPSEC_MODE__START_BIT        3
#define SHA_CONTROL_REG_IPSEC_MODE_SHA1_M			  0x0
#define SHA_CONTROL_REG_IPSEC_MODE_SHA1_HMAC_M  	  0x8
#define SHA_CONTROL_REG_IPSEC_MODE_SHA224_M 		  0x40
#define SHA_CONTROL_REG_IPSEC_MODE_SHA224_HMAC_M	  0x48		  
#define SHA_CONTROL_REG_IPSEC_MODE_SHA256_M			  0x50	  
#define SHA_CONTROL_REG_IPSEC_MODE_SHA256_HMAC_M	  0x58
#define SHA_CONTROL_REG_IPSEC_MODE_SHA384_M			  0x60	  
#define SHA_CONTROL_REG_IPSEC_MODE_SHA384_HMAC_M      0x68			  
#define SHA_CONTROL_REG_IPSEC_MODE_SHA512_M			  0x70	  
#define SHA_CONTROL_REG_IPSEC_MODE_SHA512_HMAC_M      0x78

#define SHA_CONTROL_REG_REV_SEL_OFF_F				  0x0
#define SHA_CONTROL_REG_REV_SEL_ON_F				  0x80 

#define SHA_CONTROL_REG_END_SEL_B	  				  8
#define SHA_CONTROL_REG__END_SEL__MASK				  0x0000ff00
#define SET_SHA_CONTROL_REG_END_SEL(x)				  ((x) << SHA_CONTROL_REG_END_SEL_B) & SHA_CONTROL_REG__END_SEL__MASK

#define SHA_MESSAGE_SIZE_REG                          (SHA_PREFIX+(0x7f81 << 2))   // 32 bits
#define SHA_START_REG                                 (SHA_PREFIX+(0x7f82 << 2))   // 0 bits
#define SHA_INP_DATA_READY_REG                        (SHA_PREFIX+(0x7f83 << 2))   // 0 bits
#define SHA_OUT_DATA_EMPTY_REG                        (SHA_PREFIX+(0x7f84 << 2))   // 0 bits
#define SHA_HALT_REG                                  (SHA_PREFIX+(0x7f85 << 2))   // 0 bits
#define SHA_CONTINUE_REG                              (SHA_PREFIX+(0x7f86 << 2))   // 0 bits
#define SHA_CLEAR_REG                                 (SHA_PREFIX+(0x7f87 << 2))   // 0 bits
#define SHA_MONITOR_REG                               (SHA_PREFIX+(0x7f88 << 2))   // 5 bits
#define KEY_SIZE_BYTE_REG                             (SHA_PREFIX+(0x7f89 << 2))   // 32 bits
#define KEY_START_REG                                 (SHA_PREFIX+(0x7f8A << 2))   // 0 bits
#define SHA_INITIAL_HASH_4_REG                        (SHA_PREFIX+(0x7fa0 << 2))   // 32 bits
#define SHA_INITIAL_HASH_3_REG                        (SHA_PREFIX+(0x7fa1 << 2))   // 32 bits
#define SHA_INITIAL_HASH_2_REG                        (SHA_PREFIX+(0x7fa2 << 2))   // 32 bits
#define SHA_INITIAL_HASH_1_REG                        (SHA_PREFIX+(0x7fa3 << 2))   // 32 bits
#define SHA_INITIAL_HASH_0_REG                        (SHA_PREFIX+(0x7fa4 << 2))   // 32 bits
#define SHA_KEY_ENCRY_31_REG                          (SHA_PREFIX+(0x7fc0 << 2))   // 32 bits
#define SHA_KEY_ENCRY_30_REG                          (SHA_PREFIX+(0x7fc1 << 2))   // 32 bits
#define SHA_KEY_ENCRY_29_REG                          (SHA_PREFIX+(0x7fc2 << 2))   // 32 bits
#define SHA_KEY_ENCRY_28_REG                          (SHA_PREFIX+(0x7fc3 << 2))   // 32 bits
#define SHA_KEY_ENCRY_27_REG                          (SHA_PREFIX+(0x7fc4 << 2))   // 32 bits
#define SHA_KEY_ENCRY_26_REG                          (SHA_PREFIX+(0x7fc5 << 2))   // 32 bits
#define SHA_KEY_ENCRY_25_REG                          (SHA_PREFIX+(0x7fc6 << 2))   // 32 bits
#define SHA_KEY_ENCRY_24_REG                          (SHA_PREFIX+(0x7fc7 << 2))   // 32 bits
#define SHA_KEY_ENCRY_23_REG                          (SHA_PREFIX+(0x7fc8 << 2))   // 32 bits
#define SHA_KEY_ENCRY_22_REG                          (SHA_PREFIX+(0x7fc9 << 2))   // 32 bits
#define SHA_KEY_ENCRY_21_REG                          (SHA_PREFIX+(0x7fca << 2))   // 32 bits
#define SHA_KEY_ENCRY_20_REG                          (SHA_PREFIX+(0x7fcb << 2))   // 32 bits
#define SHA_KEY_ENCRY_19_REG                          (SHA_PREFIX+(0x7fcc << 2))   // 32 bits
#define SHA_KEY_ENCRY_18_REG                          (SHA_PREFIX+(0x7fcd << 2))   // 32 bits
#define SHA_KEY_ENCRY_17_REG                          (SHA_PREFIX+(0x7fce << 2))   // 32 bits
#define SHA_KEY_ENCRY_16_REG                          (SHA_PREFIX+(0x7fcf << 2))   // 32 bits
#define SHA_KEY_ENCRY_15_REG                          (SHA_PREFIX+(0x7fd0 << 2))   // 32 bits
#define SHA_KEY_ENCRY_14_REG                          (SHA_PREFIX+(0x7fd1 << 2))   // 32 bits
#define SHA_KEY_ENCRY_13_REG                          (SHA_PREFIX+(0x7fd2 << 2))   // 32 bits
#define SHA_KEY_ENCRY_12_REG                          (SHA_PREFIX+(0x7fd3 << 2))   // 32 bits
#define SHA_KEY_ENCRY_11_REG                          (SHA_PREFIX+(0x7fd4 << 2))   // 32 bits
#define SHA_KEY_ENCRY_10_REG                          (SHA_PREFIX+(0x7fd5 << 2))   // 32 bits
#define SHA_KEY_ENCRY_9_REG                           (SHA_PREFIX+(0x7fd6 << 2))   // 32 bits
#define SHA_KEY_ENCRY_8_REG                           (SHA_PREFIX+(0x7fd7 << 2))   // 32 bits
#define SHA_KEY_ENCRY_7_REG                           (SHA_PREFIX+(0x7fd8 << 2))   // 32 bits
#define SHA_KEY_ENCRY_6_REG                           (SHA_PREFIX+(0x7fd9 << 2))   // 32 bits
#define SHA_KEY_ENCRY_5_REG                           (SHA_PREFIX+(0x7fda << 2))   // 32 bits
#define SHA_KEY_ENCRY_4_REG                           (SHA_PREFIX+(0x7fdb << 2))   // 32 bits
#define SHA_KEY_ENCRY_3_REG                           (SHA_PREFIX+(0x7fdc << 2))   // 32 bits
#define SHA_KEY_ENCRY_2_REG                           (SHA_PREFIX+(0x7fdd << 2))   // 32 bits
#define SHA_KEY_ENCRY_1_REG                           (SHA_PREFIX+(0x7fde << 2))   // 32 bits
#define SHA_KEY_ENCRY_0_REG                           (SHA_PREFIX+(0x7fdf << 2))   // 32 bits
#define SHA_KEY_DECRY_31_REG                          (SHA_PREFIX+(0x7fe0 << 2))   // 32 bits
#define SHA_KEY_DECRY_30_REG                          (SHA_PREFIX+(0x7fe1 << 2))   // 32 bits
#define SHA_KEY_DECRY_29_REG                          (SHA_PREFIX+(0x7fe2 << 2))   // 32 bits
#define SHA_KEY_DECRY_28_REG                          (SHA_PREFIX+(0x7fe3 << 2))   // 32 bits
#define SHA_KEY_DECRY_27_REG                          (SHA_PREFIX+(0x7fe4 << 2))   // 32 bits
#define SHA_KEY_DECRY_26_REG                          (SHA_PREFIX+(0x7fe5 << 2))   // 32 bits
#define SHA_KEY_DECRY_25_REG                          (SHA_PREFIX+(0x7fe6 << 2))   // 32 bits
#define SHA_KEY_DECRY_24_REG                          (SHA_PREFIX+(0x7fe7 << 2))   // 32 bits
#define SHA_KEY_DECRY_23_REG                          (SHA_PREFIX+(0x7fe8 << 2))   // 32 bits
#define SHA_KEY_DECRY_22_REG                          (SHA_PREFIX+(0x7fe9 << 2))   // 32 bits
#define SHA_KEY_DECRY_21_REG                          (SHA_PREFIX+(0x7fea << 2))   // 32 bits
#define SHA_KEY_DECRY_20_REG                          (SHA_PREFIX+(0x7feb << 2))   // 32 bits
#define SHA_KEY_DECRY_19_REG                          (SHA_PREFIX+(0x7fec << 2))   // 32 bits
#define SHA_KEY_DECRY_18_REG                          (SHA_PREFIX+(0x7fed << 2))   // 32 bits
#define SHA_KEY_DECRY_17_REG                          (SHA_PREFIX+(0x7fee << 2))   // 32 bits
#define SHA_KEY_DECRY_16_REG                          (SHA_PREFIX+(0x7fef << 2))   // 32 bits
#define SHA_KEY_DECRY_15_REG                          (SHA_PREFIX+(0x7ff0 << 2))   // 32 bits
#define SHA_KEY_DECRY_14_REG                          (SHA_PREFIX+(0x7ff1 << 2))   // 32 bits
#define SHA_KEY_DECRY_13_REG                          (SHA_PREFIX+(0x7ff2 << 2))   // 32 bits
#define SHA_KEY_DECRY_12_REG                          (SHA_PREFIX+(0x7ff3 << 2))   // 32 bits
#define SHA_KEY_DECRY_11_REG                          (SHA_PREFIX+(0x7ff4 << 2))   // 32 bits
#define SHA_KEY_DECRY_10_REG                          (SHA_PREFIX+(0x7ff5 << 2))   // 32 bits
#define SHA_KEY_DECRY_9_REG                           (SHA_PREFIX+(0x7ff6 << 2))   // 32 bits
#define SHA_KEY_DECRY_8_REG                           (SHA_PREFIX+(0x7ff7 << 2))   // 32 bits
#define SHA_KEY_DECRY_7_REG                           (SHA_PREFIX+(0x7ff8 << 2))   // 32 bits
#define SHA_KEY_DECRY_6_REG                           (SHA_PREFIX+(0x7ff9 << 2))   // 32 bits
#define SHA_KEY_DECRY_5_REG                           (SHA_PREFIX+(0x7ffa << 2))   // 32 bits
#define SHA_KEY_DECRY_4_REG                           (SHA_PREFIX+(0x7ffb << 2))   // 32 bits
#define SHA_KEY_DECRY_3_REG                           (SHA_PREFIX+(0x7ffc << 2))   // 32 bits
#define SHA_KEY_DECRY_2_REG                           (SHA_PREFIX+(0x7ffd << 2))   // 32 bits
#define SHA_KEY_DECRY_1_REG                           (SHA_PREFIX+(0x7ffe << 2))   // 32 bits
#define SHA_KEY_DECRY_0_REG                           (SHA_PREFIX+(0x7fff << 2))   // 32 bits

typedef enum {
	SHA_MEM_MODE_DMA_512		= SHA_CONTROL_REG_MEM_MODE_DMA_128_M,
	SHA_MEM_MODE_DMA_1024		= SHA_CONTROL_REG_MEM_MODE_DMA_1024_M, 
	SHA_MEM_MODE_DMA_CPU2K		= SHA_CONTROL_REG_MEM_MODE_DMA_CPU2K_M
} sha_mem_mode_t;

typedef enum {
	SHA_IPSEC_OP_SEL_ENCRYPT	= SHA_CONTROL_REG_IPSEC_OP_SEL_ENCRYPT_F,
	SHA_IPSEC_OP_SEL_DECRYPT	= SHA_CONTROL_REG_IPSEC_OP_SEL_DECRYPT_F
} sha_ipsec_op_t;

typedef enum {
    SHA_MODE_SHA1				 = SHA_CONTROL_REG_IPSEC_MODE_SHA1_M	,		
    SHA_MODE_SHA1_HMAC		     = SHA_CONTROL_REG_IPSEC_MODE_SHA1_HMAC_M,  	
    SHA_MODE_SHA224			     = SHA_CONTROL_REG_IPSEC_MODE_SHA224_M 	,	
    SHA_MODE_SHA224_HMAC		 = SHA_CONTROL_REG_IPSEC_MODE_SHA224_HMAC_M,		
    SHA_MODE_SHA256			     = SHA_CONTROL_REG_IPSEC_MODE_SHA256_M	,		  
    SHA_MODE_SHA256_HMAC		 = SHA_CONTROL_REG_IPSEC_MODE_SHA256_HMAC_M,	
    SHA_MODE_SHA384			     = SHA_CONTROL_REG_IPSEC_MODE_SHA384_M	,		  
    SHA_MODE_SHA384_HMAC	     = SHA_CONTROL_REG_IPSEC_MODE_SHA384_HMAC_M,    		  
    SHA_MODE_SHA512			     = SHA_CONTROL_REG_IPSEC_MODE_SHA512_M	,		  
    SHA_MODE_SHA512_HMAC         = SHA_CONTROL_REG_IPSEC_MODE_SHA512_HMAC_M    
} sha_ipsec_mode_t;

typedef enum {
	SHA_REV_BIT_OFF	 				 = SHA_CONTROL_REG_REV_SEL_OFF_F,
	SHA_REV_BIT_ON					 = SHA_CONTROL_REG_REV_SEL_ON_F 
} sha_bit_rev_t;


typedef struct {
	sha_mem_mode_t		sha_mem_mode;
	sha_ipsec_op_t		sha_ipsec_op;
	sha_ipsec_mode_t	sha_ipsec_mode;
	sha_bit_rev_t		sha_bit_rev;
	unsigned char		sha_reg_end;
	unsigned char*		key;
	int					key_len;
	int					len;
	char				*plain_text;
	char				*digest;
} sha_params_t;

typedef struct {
	char				name[20];
	int					idx;  
} sha_data_t;

#define		SHA_HW_BUFFER_SIZE		  (1024 *2)
#define		SHA_DATA_BUFFER_MAX_SIZE  (1024 *8)

#endif //BRCM_ACRYPT_SHA_H


																								
