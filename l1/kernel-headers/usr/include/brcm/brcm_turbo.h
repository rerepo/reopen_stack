#ifndef BRCM_TURBO_H
#define BRCM_TURBO_H

#define TURBO_PREFIX						0xBFDC0000

//3G BLOCK
#define TURBO_3G_IN_DATA_BUFFER				TURBO_PREFIX
#define TURBO_3G_OUT_DATA_BUFFER			(TURBO_PREFIX+(8192 * 4))

#define TURBO_3G_I_REG						(TURBO_PREFIX+(8704 * 4))
#define TURBO_3G_K_REG						(TURBO_PREFIX+(8705 * 4))
#define TURBO_3G_C_REG						(TURBO_PREFIX+(8706 * 4))
#define TURBO_3G_D_REG						(TURBO_PREFIX+(8707 * 4))
#define TURBO_3G_E_REG						(TURBO_PREFIX+(8708 * 4))
#define TURBO_3G_F_REG						(TURBO_PREFIX+(8709 * 4))
#define TURBO_3G_G_REG						(TURBO_PREFIX+(8710 * 4))
#define TURBO_3G_H_REG						(TURBO_PREFIX+(8711 * 4))
#define TURBO_3G_NU_REG						(TURBO_PREFIX+(8712 * 4))
#define TURBO_3G_MAP_C_REG					(TURBO_PREFIX+(8713 * 4))
#define TURBO_3G_N_HALF_REG					(TURBO_PREFIX+(8714 * 4))
#define TURBO_3G_SLD_REG					(TURBO_PREFIX+(8715 * 4))
#define TURBO_3G_LIMZ_REG					(TURBO_PREFIX+(8716 * 4))
#define TURBO_3G_M_REG						(TURBO_PREFIX+(8717 * 4))
#define TURBO_3G_ZTH_REG					(TURBO_PREFIX+(8718 * 4))
#define TURBO_3G_N_REG						(TURBO_PREFIX+(8719 * 4))
#define TURBO_3G_DELAY_REG					(TURBO_PREFIX+(8720 * 4))

#define TURBO_3G_Q0_REG						(TURBO_PREFIX+(8736 * 4))
#define TURBO_3G_Q1_REG						(TURBO_PREFIX+(8737 * 4))
#define TURBO_3G_Q2_REG						(TURBO_PREFIX+(8738 * 4))
#define TURBO_3G_Q3_REG						(TURBO_PREFIX+(8739 * 4))
#define TURBO_3G_Q4_REG						(TURBO_PREFIX+(8740 * 4))
#define TURBO_3G_Q5_REG						(TURBO_PREFIX+(8741 * 4))
#define TURBO_3G_Q6_REG						(TURBO_PREFIX+(8742 * 4))
#define TURBO_3G_Q7_REG						(TURBO_PREFIX+(8743 * 4))
#define TURBO_3G_Q8_REG						(TURBO_PREFIX+(8744 * 4))
#define TURBO_3G_Q9_REG						(TURBO_PREFIX+(8745 * 4))
#define TURBO_3G_Q10_REG					(TURBO_PREFIX+(8746 * 4))
#define TURBO_3G_Q11_REG					(TURBO_PREFIX+(8747 * 4))
#define TURBO_3G_Q12_REG					(TURBO_PREFIX+(8748 * 4))
#define TURBO_3G_Q13_REG					(TURBO_PREFIX+(8749 * 4))
#define TURBO_3G_Q14_REG					(TURBO_PREFIX+(8750 * 4))
#define TURBO_3G_Q15_REG					(TURBO_PREFIX+(8751 * 4))
#define TURBO_3G_Q16_REG					(TURBO_PREFIX+(8752 * 4))
#define TURBO_3G_Q17_REG					(TURBO_PREFIX+(8753 * 4))
#define TURBO_3G_Q18_REG					(TURBO_PREFIX+(8754 * 4))
#define TURBO_3G_Q19_REG					(TURBO_PREFIX+(8755 * 4))

#define TURBO_DATA_IN_ORDER_REG				(TURBO_PREFIX+(8960 * 4))
#define TURBO_3G_MEM_ACCS_REG				(TURBO_PREFIX+(8961 * 4))
#define TURBO_3G_CLEAR_REG					(TURBO_PREFIX+(8962 * 4))
#define TURBO_3G_START_REG					(TURBO_PREFIX+(8963 * 4))
#define TURBO_3G_ENABLE_REG					(TURBO_PREFIX+(8964 * 4))
#define TURBO_3G_ERR_CNT_REG				(TURBO_PREFIX+(8965 * 4))

//CDM2000 block
#define TURBO_CDMA_IN_DATA_BUFFER			(TURBO_PREFIX+(12288 * 4))
#define TURBO_CDMA_OUT_DATA_BUFFER			(TURBO_PREFIX+(36864 * 4))
				
#define TURBO_CDMA_MEM_ACCS_REG				(TURBO_PREFIX+(37632 * 4))
#define TURBO_CDMA_CLEAR_REG				(TURBO_PREFIX+(37633 * 4))
#define TURBO_CDMA_START_REG				(TURBO_PREFIX+(37634 * 4))
#define TURBO_CDMA_ENABLE_REG				(TURBO_PREFIX+(37635 * 4))
#define TURBO_CDMA_ERR_CNT_REG				(TURBO_PREFIX+(37636 * 4))
#define TURBO_CDMA_F1I_REG					(TURBO_PREFIX+(37637 * 4))
#define TURBO_CDMA_F2I_REG					(TURBO_PREFIX+(37638 * 4))
#define TURBO_CDMA_S3G_REG					(TURBO_PREFIX+(37639 * 4))
#define TURBO_CDMA_N_REG					(TURBO_PREFIX+(37640 * 4))
#define TURBO_CDMA_C_REG					(TURBO_PREFIX+(37641 * 4))
#define TURBO_CDMA_CS_REG					(TURBO_PREFIX+(37642 * 4))
#define TURBO_CDMA_NI_REG					(TURBO_PREFIX+(37643 * 4))
#define TURBO_CDMA_LIMZ_REG					(TURBO_PREFIX+(37644 * 4))
#define TURBO_CDMA_DELAY_REG				(TURBO_PREFIX+(37645 * 4))
#define TURBO_CDMA_M_REG					(TURBO_PREFIX+(37646 * 4))
#define TURBO_CDMA_MODE_REG					(TURBO_PREFIX+(37647 * 4))
#define TURBO_CDMA_ZTH_REG					(TURBO_PREFIX+(37648 * 4))
#define TURBO_CDMA_K_REG					(TURBO_PREFIX+(37649 * 4))
#define TURBO_CDMA_SM_REG					(TURBO_PREFIX+(37650 * 4))
#define TURBO_CDMA_CI_REG					(TURBO_PREFIX+(37651 * 4))
#define TURBO_CDMA_CA_REG					(TURBO_PREFIX+(37652 * 4))
#define TURBO_CDMA_SCLZ_REG					(TURBO_PREFIX+(37653 * 4))
#define TURBO_CDMA_XDE_REG					(TURBO_PREFIX+(37654 * 4))
#define TURBO_CDMA_FS_REG					(TURBO_PREFIX+(37655 * 4))
#define TURBO_CDMA_VA_REG					(TURBO_PREFIX+(37656 * 4))
#define TURBO_CDMA_TCM_REG					(TURBO_PREFIX+(37657 * 4))
#define TURBO_CDMA_SLD_REG					(TURBO_PREFIX+(37658 * 4))
#define TURBO_CDMA_TB_REG					(TURBO_PREFIX+(37659 * 4))
#define TURBO_CDMA_NA_REG					(TURBO_PREFIX+(37660 * 4))
#define TURBO_CDMA_CWE_REG					(TURBO_PREFIX+(37661 * 4))

#define VITERBI_DECODE_RATE_3 3
#define VITERBI_DECODE_RATE_2 2

#define HW_BLOCK_3G 1
#define HW_BLOCK_CDMA2000 2


#ifndef PRC_CB_T
#define PRC_CB_T
typedef struct
{
	//coding_type is VITERBI_DECODING_2=1, VITERBI_DECODING_3=2, TURBO_DECODING=3
	unsigned char		coding_type;
	//Number of bits to be decoded.
	unsigned short		k;
	//Pointer to input softbits.
	char				*in_bits;
	//Pointer to decoded bits.
	unsigned int		*out_bits;
	//Virtual Address for the mmap memory allocated.
	unsigned int		v_addr;
	//Use DMA is this flag is set.
	unsigned char       use_dma_flag;
} percello_cb_t;
#endif

#define VITERBI_DECODING_2			1
#define VITERBI_DECODING_3			2
#define TURBO_DECODING				3
#define TEST_TURBO_DECODING    		4	////TEMP
#define TEST_VITERBI_DECODING    	5	////TEMP

#define FRX_NUM_OF_QS_IN_DB                      19
#define FRX_NUM_OF_QS_OPTIONS                    41
#define FRX_NUM_OF_TURBO_DB_OPTIONS              51
#define FRX_QS_OPTIONS_NUM_OF_COMPRESSED_WORDS   ((FRX_NUM_OF_QS_IN_DB + 1) >> 1)
#define FRX_RAB_TFCI_T_TURBO_C_MASK              0x1ff
#define FRX_RAB_TFCI_T_TURBO_D_LOCATION          9
#define FRX_RAB_TFCI_T_TURBO_D_MASK              3
#define FRX_RAB_TFCI_T_TURBO_D_BITS_NUM          2
#define FRX_RAB_TFCI_T_TURBO_F_LOCATION          11
#define FRX_RAB_TFCI_T_TURBO_F_MASK              3
#define FRX_RAB_TFCI_T_TURBO_F_BITS_NUM          2
#define FRX_RAB_TFCI_T_TURBO_G_LOCATION          13
#define FRX_RAB_TFCI_T_TURBO_G_MASK              1
#define FRX_RAB_TFCI_T_TURBO_G_BITS_NUM          1
#define FRX_RAB_TFCI_T_TURBO_H_LOCATION          14
#define FRX_RAB_TFCI_T_TURBO_H_MASK              3
#define FRX_RAB_TFCI_T_TURBO_H_BITS_NUM          2
#define FRX_RAB_TFCI_T_TURBO_E_LOCATION          16
#define FRX_RAB_TFCI_T_TURBO_E_MASK              0x1ff
#define FRX_RAB_TFCI_T_TURBO_E_BITS_NUM          9
#define FRX_RAB_TFCI_T_TURBO_DBI_LOCATION        25
#define FRX_RAB_TFCI_T_TURBO_DBI_MASK            0x3f
#define FRX_RAB_TFCI_T_TURBO_DBI_BITS_NUM        6

#endif

