#ifndef BRCM_DSP_H
#define BRCM_DSP_H


#define DSP_WRITE 				0
#define DSP_READ 				1
#define DSP_LOAD				2
#define DSP_COMPARE				3
#define DSP_WRITE_PHYSICAL		4
#define DSP_READ_PHYSICAL		5
#define CPU_WRITE 				6		
#define CPU_READ 				7
#define	AFC_DAC					8
#define	UTC_READ				9
#define	DSP_MULTIPLE_READ_WRITE 10
#define	AFC_DAC_INIT			11
#define DSP_GET_CPU_STAT		12
#define	UTC_MFC_READ			13
#define UTC_RAW_READ            14
#define DSP_MEM_TEST            15
#define DSP_MEM_TEST_1          16
#define DSP_GET_CPU_STAT_SMP    17

struct dsp_block
{
	unsigned int control;
	unsigned int address;
	unsigned int data;
	unsigned int bitmask;
	unsigned int status;
};

#define DSP_PREFIX						0xbe040000 //??????


#define DSP_BLOCK_ADDR					0xBE0557E8
#define CELIVERO_CPU_DSP_INT			0xBE0D8400

#define DSP_OPCODE_READ			1
#define DSP_OPCODE_WRITE		2

#define DSP_DMEM_MEM_TYPE		0	/* DMEM = internal DSP data memory */
#define DSP_PMEM_MEM_TYPE		1	/* PMEM = peripheral memory (e_fle memory) */
#define DSP_DDR_MEM_TYPE		2
#define DSP_PRBUS_MEM_TYPE		3

#define DSP_ABORT_ILLEGAL_ADD	1	/* an address not within the valid address range was requested */
#define DSP_ABORT_ILLEGAL_OPCODE	2	/* an illegal opcode was given (an opcode different than read or write opcodes) */
#define DSP_READ_OP_COMPLETE	3	/* the requested read operation was complete successfully 	\
						(The read data is ready in the input/output data DPR word) */
#define DSP_WRITE_OP_COMPLETE	4	/* the requested write operation was completed successfully */
#define DSP_INDICATION_NOT_READY	0	/* this value should be set by L1 before triggering the interrupt towards the DSP */
 
#define FREQ_SYNTH			0
#define SIGMA_DELTA			1

typedef struct {
	unsigned long usec;
	unsigned long sec;
} prc6000_utc_t;


typedef struct {
	unsigned long		usec;
	unsigned long		sec;
	unsigned long		chip;
	unsigned long		sfn;
}	prc_timestamp_t;


typedef struct {
	unsigned short		type;
	unsigned long		base;
	unsigned long		offset;
}	afc_dac_t;



typedef struct {
   unsigned long addr;
   unsigned long data;
   unsigned long mask;
   unsigned long length;
} dsp_compare_t;

typedef struct {
	unsigned long addr;
	unsigned long data;
	long		  type;
} dsp_read_write_t;


#ifdef __BRCM_DSP__
static int dsp_write(unsigned long addr,unsigned long data, long type);
static int dsp_read(unsigned long addr, long type, unsigned long *data);
static int brcm_dsp_driver_cmd_demux(unsigned long cmd, unsigned long arg,void *arg1);
#define EXTERN 
#else
#define EXTERN extern
#endif

#undef EXTERN

#endif


