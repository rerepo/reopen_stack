#ifndef BRCM_RSA_H
#define BRCM_RSA_H

#ifdef __KERNEL__
#define U32 u32
#define U16 u16
#define U8 u8
#else
#define U32 unsigned long
#define U16 unsigned short
#define U8 unsigned char
#endif

#include "brcm_l1_common_interface.h"

#define RSA_ENCRYPT						0
#define RSA_DECRYPT						1
#define RSA_SET_PRIVATE_KEY				2

#define RSA_MAX_PRVT_KEY_SIZE_BITS		(3104)
#define RSA_MAX_MODULUS_SIZE_BITS		(2080)
#define RSA_MAX_DATA_SIZE_BYTES			(2*1024)

#define RSA_REGS_BASE					(0xBE400000)
#define RSA_REGS_RAM_DATA				(RSA_REGS_BASE + 0x00000)

#define RSA_REGS_PRVT_KEY				(RSA_REGS_BASE + 0x18000)
#define RSA_REGS_PUB_KEY				(RSA_REGS_BASE + 0x18184)
#define RSA_REGS_MODULUS				(RSA_REGS_BASE + 0x18188)

#define RSA_REGS_CTRL_REG				(RSA_REGS_BASE + 0x1C000)
#define RSA_REGS_MEM_SIZE				(RSA_REGS_BASE + 0x1C004)
#define RSA_REGS_KEY_START				(RSA_REGS_BASE + 0x1C008)
#define RSA_REGS_RSA_START				(RSA_REGS_BASE + 0x1C00C)
#define RSA_REGS_INP_DATA_RDY			(RSA_REGS_BASE + 0x1C010)
#define RSA_REGS_OUT_DATA_EMP			(RSA_REGS_BASE + 0x1C014)
#define RSA_REGS_RSA_CLEAR				(RSA_REGS_BASE + 0x1C018)
#define RSA_REGS_MONITOR_SEL			(RSA_REGS_BASE + 0x1C01C)

#define RSA_OTPMEM_START				(RSA_REGS_BASE + 0x1E000)
#define RSA_OTPMEM_CTRL					(RSA_REGS_BASE + 0x1E400)
#define RSA_OTPMEM_STATUS				(RSA_REGS_BASE + 0x1E410)
#define RSA_OTPMEM_ADDR					(RSA_REGS_BASE + 0x1E430)

#define RSA_CTRL_REG_READ_ALL_OTP		0x13
#define RSA_CTRL_REG_PROG_ENABLE		0x14
#define RSA_CTRL_REG_PROG_ALL_OTP		0x17

#define RSA_STATUS_REG_PROG_FAIL		0x20
#define RSA_STATUS_REG_PROG_NOT_ALLOWED	0x200

#define CLKGEN_RESET_REGISTER			(0xBEC02024)
#define CLKGEN_RSA_RESET_OFFSET			(5)

#define RSA_STATUS_REG_TIMEOUT			100000000

	typedef struct {
	void *prvt_key; /* NULL if using OTP key, otherwise DMA-able mmap'd virtual pointer, given in LITTLE-ENDIAN format */
	U32 prvt_key_len; /* 0 if using OTP key, otherwise key length in bits (2048,1024,512) */

	U32 pub_key; /* 32-bit public key value */

	void *modulus; /* DMA-able mmap'd virtual pointer */
	U32 modulus_len; /* Modulus length in bits (2048,1024,512) */

	void *input_data; /* DMA-able mmap'd virtual pointer */
	U32 input_data_len; /* In bytes */

	void *output_data; /* DMA-able mmap'd virtual pointer, can be equal to input_data or NULL to perform in-place RSA */
} rsa_params_t;

#define OTP_INT_LEN		64
typedef struct {
	unsigned long 	otpmem[OTP_INT_LEN];
} rsa_key_t; 


#ifdef __KERNEL__

#ifdef __RSA_DRIVER__
#define EXTERN
#else
#define EXTERN extern
#endif

/* Define any functions here */

EXTERN int brcm_rsa_encrypt(rsa_params_t *params, int use_otp_key);
EXTERN int brcm_rsa_decrypt(rsa_params_t *params, int use_otp_key);

#undef EXTERN
#endif /* __KERNEL__ */
#endif 

