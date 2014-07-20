#include "ipsec_regs.h"

#define OK_D						2147483646		// Clear value
#define ERROR_D						99999999



#define TIMEOUT_LONG				10000000			// Long timeout definition
#define TIMEOUT_SHORT				100					// Short timeout definition
#define WAIT_AFTER_END				10000
#define MARK_OK						" ===================== "		// for printing messages
#define MARK_ERR					" ===X=X=X=X=X=X=X=X=X= "		// for printing messages
#define TIME_STAMP					sc_time_stamp().to_string().c_str()

#define WAIT_REG_TEST				1001
#define WAIT_DEFAULT_REG_TEST		1002
#define WAIT_MEM_TEST				1003

#define DDR_OFFSET_TEST				0x2000

#define DDR_OFFSET_FOR_TEST_IND 	(DDR_OFFSET_TEST + 0x0)			// 0x2000
#define TB_wait_for_DSP				(DDR_OFFSET_FOR_TEST_IND + 0) 	// Control address used by the test banch to wait for DSP 
#define DSP_wait_for_TB				(DDR_OFFSET_FOR_TEST_IND + 1)	// Control address used by the DSP to wait for test banch
#define TB_wait_for_CPU				(DDR_OFFSET_FOR_TEST_IND + 2)	// Control address used by the test banch to wait for CPU
#define CPU_wait_for_TB				(DDR_OFFSET_FOR_TEST_IND + 3)	// Control address used by the CPU to wait for test banch
#define CPU_wait_for_DSP			(DDR_OFFSET_FOR_TEST_IND + 4)
#define DSP_wait_for_CPU			(DDR_OFFSET_FOR_TEST_IND + 5)

#define DDR_OFFSET_FOR_TEST_ERROR	(DDR_OFFSET_TEST + 0x100)		// 0x2100
#define DSP_wait_error				(DDR_OFFSET_FOR_TEST_ERROR + 0)	// Address used to indicate error type for DSP wait process
#define CPU_wait_error				(DDR_OFFSET_FOR_TEST_ERROR + 1)	// Address used to indicate error type for CPU wait process
#define DSP_general_error			(DDR_OFFSET_FOR_TEST_ERROR + 2)	// Address used to indicate error type for DSP 
#define CPU_general_error			(DDR_OFFSET_FOR_TEST_ERROR + 3)	// Address used to indicate error type for CPU 
#define DSP_HW_error				(DDR_OFFSET_FOR_TEST_ERROR + 4)
#define DSP_error_report1			(DDR_OFFSET_FOR_TEST_ERROR + 5)
#define DSP_error_report2			(DDR_OFFSET_FOR_TEST_ERROR + 6)
#define DSP_error_report3			(DDR_OFFSET_FOR_TEST_ERROR + 7)
#define DSP_error_report4			(DDR_OFFSET_FOR_TEST_ERROR + 8)

#define CPU_error_report1			(DDR_OFFSET_FOR_TEST_ERROR + 9)
#define CPU_error_report2			(DDR_OFFSET_FOR_TEST_ERROR + 10)
#define CPU_error_report3			(DDR_OFFSET_FOR_TEST_ERROR + 11)
#define CPU_error_report4			(DDR_OFFSET_FOR_TEST_ERROR + 12)

#define TEST_RESULTS_ADDR			(DDR_OFFSET_TEST + 0x20000)

#define DDR2_REGS_DB			    (DDR_OFFSET_TEST + 0x1000)

#define DDR2_DB			            (DDR_OFFSET_TEST + 0x2000)


// M4K Program memory
#define  PROGRAM_MEM		0x10000  // 0x10000-0x15FFC : program memory (4096 bytes)
#define  PROGRAM_MEM_LEN	0x6000 //0x6000
#define  program_mem		(ipsec_PREFIX + PROGRAM_MEM)

// M4K Data memory
#define  DATA_MEM		0x1C000  // 0x1C000-0x1EFFC : program memory (4096 bytes)
#define  DATA_MEM_LEN	0x3000  // 0x3000
#define  data_mem		(ipsec_PREFIX + DATA_MEM)
// SADB
#define  SADB_MEM		0x4000  // 0x4000-0x5FFC : SADB
#define  SADB_MEM_LEN	0x2000
#define  sadb_mem		(ipsec_PREFIX + SADB_MEM)

// Buffers
#define  BUF0_MEM		0x8000  // 0x8000-0x887C : buffer-0  (2176 bytes)
#define  BUF0_MEM_LEN	0x900
#define  buf0_mem		(ipsec_PREFIX + BUF0_MEM)

#define  RES0_MEM		0x8A00  // 0x8900-0x89FC : mini-buffer (256 bytes)
#define  RES0_MEM_LEN	0x80
#define  res0_mem		(ipsec_PREFIX + RES0_MEM)

#define  BUF1_MEM		0x9000  // 0x9000-0x987C : buffer-0  (2176 bytes)
#define  BUF1_MEM_LEN	0x900
#define  buf1_mem		(ipsec_PREFIX + BUF1_MEM)

#define  RES1_MEM		0x9A00  // 0x9900-0x99FC : mini-buffer (equiv to 0x0900-0x09FC)
#define  RES1_MEM_LEN	0x80
#define  res1_mem		(ipsec_PREFIX + RES1_MEM)

// FIFOs
#define  DESC_FIFO		0xA180  //  Descriptor FIFO
#define  desc_fifo		ipsec_PREFIX + DESC_FIFO  //  Descriptor FIFO
#define  RESULT_FIFO	0xA140  //  Result FIFO
#define  result_fifo		ipsec_PREFIX + RESULT_FIFO  //  Result FIFO


#define SHA_COFF_LEN	(204*4) // 816 Bytes

#define	MAX_DATA_LENGTH	110000


#define	DDR_SADB_TABLE		80000
#define	DDR_INP_DATA_PTR	100000
#define	DDR_RES_DATA_PTR	200000

#define	HOST_TO_CPU_MSG_IND	30000
#define	HOST_TO_CPU_MSG		30002
#define	CPU_TO_HOST_MSG_IND	60000
#define	CPU_TO_HOST_MSG		60002

#define	DDR2_SEGMENT_SIZE	(CPU_TO_HOST_MSG_IND - HOST_TO_CPU_MSG_IND)

#define	NOPS_TO_WAIT_FOR_RESULT	8


#define	TEST_REGISTERS		1
#define	TEST_MEMORY			2
#define	TEST_SADB_MEMORY	3
#define	TEST_AES			4
#define	TEST_CLEAR_SIG		5
#define	PROGRAM_SHA_LOAD	6
#define	TEST_ZPU			7
#define	TEST_SHA			8
#define	TEST_FIFO			9
#define	TEST_SADB_DMA		10
#define TEST_SHA_RESET      11
#define TEST_AES_SHA		12

#define	STATUS_OK		1
#define	STATUS_FAIL		0
#define SA_SIZE			50
#define CPU_MODE		0
#define	DESC_MODE		1

#define ECB				0x0
#define	CFB				0x1
#define	CBC				0x2
#define	CTR				0x3
#define CTR_IV			0x4
#define CCM_A			0x5
#define CCM_E			0x6
#define CCM_IV			0x7
#define	EEA2			0x8
#define	EIA2			0x9
#define XCBC_128		0xa
#define XCBC_96			0xb

#define HASH_SHA1		0x0
#define	HMAC_SHA1		0x8
#define	HASH_SHA224		0x4
#define	HMAC_SHA224		0xc
#define HASH_SHA256		0x5
#define HMAC_SHA256		0xd
#define HASH_SHA384		0x6
#define HMAC_SHA384		0xe
#define HASH_SHA512		0x7	
#define HMAC_SHA512		0xf

#define AES_OP			(0x0 << 14)
#define SHA_OP			(0x1 << 14)
#define AES_SHA_OP		(0x2 << 14)
#define NULL_OP			(0x3 << 14)


#define CTR_IV_CTR		0x24

#define SPI_BASE1		0xaaaaaaaa
//#define SPI_BASE2		0xbbbbbbbb
#define SPI_BASE2		0xcccccccc
#define SPI_BASE3		0xdddddddd
#define DA_ADDR1		0x12345000
#define ENDIANESS_16_BIT 0xdd
#define ENDIANESS_32_BIT 0x77

#define CRYPTO_AES			0xF
#define CRYPTO_SHA			0xF0
#define CRYPTO_CTR			0x700
#define CRYPTO_ENC_DEC		0x800
#define CRYPTO_KEY_SIZE		0x3000
#define CRYPTO_AES_SHA		0xC000
#define CRYPTO_ESP_AH		0x10000
#define CRYPTO_TUNNEL		0x20000
#define CRYPTO_RAW			0x40000
#define CRYPTO_SEQ_SIZE		0x80000

#define	WAIT_TIMEOUT	10000

#define SELF_MEM_TEST_END	0x1
#define FIFO_TEST			0x2
#define FIFO_TEST1			0x3
#define SADB_DMA_TEST		0x4

#define FIFO_TEST_END		0x2
#define DESC_FIFO_DEPTH		256
#define RES_FIFO_DEPTH		31




#define PRC_CPUH_WAIT_ON_MEM(_mem_add,_wait_for_val,_timeout,_if_timeout)\
    _if_timeout = true;\
    for( long long _i = 0; _i < _timeout; _i++ )\
    {\
        wait();\
        if( PRC_CPUH_READ( _mem_add) == _wait_for_val )\
        {\
            _if_timeout = false;\
            break;\
        }\
    }


typedef struct CRYPTO_TEST_INFO
{
	int id;
	int raw_ipsec;						// Raw, IPSec
	int	cpu_desc;						// CPU, Descriptors
	int spi;							// SPI value for CPU mode
	int esp_ah;							// ESP, AH mode 
	int tunnel_trans;					// Tunnel, transport mode
	int dest_add;						// Destination address for CPU mode
	int endian;
	int reverse;
	int seq_num_size;					// control the size of the sequence number; 32 bits = "0", 64 bits = "1"
	int int_mask;						// interrupt mask
	int crypto_mode;					
	int reset_operation;				// Reset operation control
	int dir;							// for CPU mode
	int ctr_counter_size;				// for CPU mode
	int aes_length;
	int aes_ref_length;						// for CPU mode
	int aes_key_size;						
	u8	aes_key[128];						// for CPU mode
	u8	aes_iv[128];						// for CPU mode
	u8	aes_text[MAX_DATA_LENGTH];			// for CPU mode
	u8	aes_reference[MAX_DATA_LENGTH];		// for CPU mode
	int sha_length;
	int sha_ref_length;						// for CPU mode
	int sha_key_size;						
	u8	sha_key[128];						// for CPU mode
	u8	sha_text[MAX_DATA_LENGTH];			// for CPU mode
	u8	sha_reference[MAX_DATA_LENGTH];		// for CPU mode
} CRYPTO_TEST_INFO;


typedef struct  REG_TEST_INFO
{
	int reg_addr;
	int reg_bits;
} REG_TEST_INFO;

typedef struct TEST_REQ_INFO
{
	int msg_len;
	int	test_id;
	union {
		CRYPTO_TEST_INFO	test_info;
		REG_TEST_INFO		reg_test_info;
	}u;
} TEST_REQ_INFO;

typedef struct TEST_CNF_INFO
{
	int msg_len;
	int	test_id;
	int status;
	int addr;
	u8 result[MAX_DATA_LENGTH];
} TEST_CNF_INFO;

u8 chartou8 (char in_data);

typedef struct CONTROL
   { 
 	   unsigned int cpu_descriptor		: 1;   // Select between CPU and Descriptor mode CPU = "0", Descriptor = "1"
       unsigned int ipsec_en			: 1;   // Enables IPSEC header and tail chacking Disable = "0", Enable = "1"
       unsigned int illegal_en			: 1;   // Enable result report in case of illegal packet (e.g. authentication fail); Disable = "0", Enable = "1"
	   unsigned int dma_w_endianess		: 8;   // Control the block endianess no change = "00", 32 bit = "0x77", 16 bits = "0xdd"
       unsigned int dma_w_reverse		: 1;   // Bit reverse; Disable = "0", Enable = "1"	
 	   unsigned int dma_r_endianess		: 8;   // Control the block endianess no change = "00", 32 bit = "0x77", 16 bits = "0xdd"
       unsigned int dma_r_reverse		: 1;   // Bit reverse; Disable = "0", Enable = "1"	
       unsigned int seq_num_size		: 1;   // control the size of the sequence number; 32 bits = "0", 64 bits = "1"
       unsigned int sadb_access_cont	: 1;   // Enables the CPU to request an access to the SADB. No_request = "0", request = "1"
       unsigned int self_test_req		: 1;   // Request memory self test from the internal CPU
	   unsigned int reserve				: 8;
   }CONTROL; 

