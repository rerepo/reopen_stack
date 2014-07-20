#ifndef BRCM_F8_H
#define BRCM_F8_H


/* system call command macros */
#define F8_CIPHER			0
#define START_SET			1
#define READ_STATUS			2
#define F8_SETUP			3


#define		MAX_F8_TIMEOUT			20

#define     F8_ENDIAN_NO_CHANGE     0
#define     F8_ENDIAN_SWAP_SHORT    1
#define     F8_ENDIAN_SWAP_LONG     2

#define     F8_NO_BIT_REVERSE       0
#define     F8_BIT_REVERSE          1

#define     F8_CIPHER_MODE          0
#define     F8_KEYSTREAM_MODE       1

#define     F8_UPLINK               0
#define     F8_DOWNLINK             1

#define     F8_NO_BIT_SHIFT         0
#define     F8_8_BIT_SHIFT          1
#define     F8_16_BIT_SHIFT         2
#define     F8_24_BIT_SHIFT         3

#define		MAX_PDU_SIZE			96 /* = 768/8 */
#define     MAX_NUM_OF_BITS_IN_PDU  768


#define	F9_SELECTION_MASK		0x01
#define	DL_DIRECTION_MASK		0x02
#define	MODE_BUFFER_MASK		0x04
#define	ENDIAN_16_MASK			0x08
#define	ENDIAN_32_MASK			0x10
#define	REVERSE_MASK			0x20
#define	X_READY_MASK			0x01
#define	Y_READY_MASK			0x02

#define	X_SET					0
#define	Y_SET					1


#define	ADDR_HOST_CONT_X			(F8F9_BASE_ADDR + 0x0)
#define	ADDR_HOST_CONT_Y			(F8F9_BASE_ADDR + 0x1*4)
#define	ADDR_STATUS					(F8F9_BASE_ADDR + 0xC*4)
#define	ADDR_BEARER_X				(F8F9_BASE_ADDR + 0x2*4)
#define	ADDR_BEARER_Y				(F8F9_BASE_ADDR + 0x3*4)
#define	ADDR_CK_IK_0_X				(F8F9_BASE_ADDR + 0x4*4)
#define	ADDR_CK_IK_1_X				(F8F9_BASE_ADDR + 0x5*4)
#define	ADDR_CK_IK_2_X				(F8F9_BASE_ADDR + 0x6*4)
#define	ADDR_CK_IK_3_X				(F8F9_BASE_ADDR + 0x7*4)
#define	ADDR_CK_IK_0_Y				(F8F9_BASE_ADDR + 0x8*4)
#define	ADDR_CK_IK_1_Y				(F8F9_BASE_ADDR + 0x9*4)
#define	ADDR_CK_IK_2_Y				(F8F9_BASE_ADDR + 0xA*4)
#define	ADDR_CK_IK_3_Y				(F8F9_BASE_ADDR + 0xB*4)
#define	ADDR_STATUS					(F8F9_BASE_ADDR + 0xC*4)
#define	ADDR_LEN_X					(F8F9_BASE_ADDR + 0x10*4)
#define	ADDR_LEN_Y					(F8F9_BASE_ADDR + 0x11*4)
#define	ADDR_FRESH					(F8F9_BASE_ADDR + 0x12*4)
#define	ADDR_COUNT_X				(F8F9_BASE_ADDR + 0x13*4)
#define	ADDR_COUNT_Y				(F8F9_BASE_ADDR + 0x14*4)
#define	ADDR_SHIFT_X				(F8F9_BASE_ADDR + 0x15*4)
#define	ADDR_SHIFT_Y				(F8F9_BASE_ADDR + 0x16*4)
#define	ADDR_START_X				(F8F9_BASE_ADDR + 0x20*4)
#define	ADDR_START_Y				(F8F9_BASE_ADDR + 0x21*4)
#define	ADDR_MON_BUS				(F8F9_BASE_ADDR + 0x30*4)
#define	ADDR_X_BUFFER				(F8F9_BASE_ADDR + 0x40*4)
#define	ADDR_Y_BUFFER				(F8F9_BASE_ADDR + 0x80*4)


typedef struct {
 int host_cont_addr;	
 int bearer_addr;
 int key_0_addr	;	
 int key_1_addr	;	
 int key_2_addr	;	
 int key_3_addr	;	
 int len_addr	;	
 int count_addr	;	
 int shift_addr	;	
 int start_addr	;	
 int status_mask;	
 int buffer_addr;	
} brcm_f8_set_t;



typedef struct
{
    unsigned int 	len;
    unsigned char   key[16];
    unsigned int    count;
    unsigned int  	bearer;
    unsigned int	direction;
    unsigned int	shift_val;
} brcm_cipher_params_t;

typedef struct
{
      unsigned char	 *in_pdu;
      unsigned char  *out_pdu;
} brcm_f8_data_t; 


typedef struct
{
  brcm_cipher_params_t  config_params;                  
  int						number_of_pdu;
  brcm_f8_data_t		*pdu_list;
  int						mode;
} brcm_cipher_t;


typedef struct
{
	unsigned long val[2];
} brcm_f8_64_bit_res_t;

#endif
