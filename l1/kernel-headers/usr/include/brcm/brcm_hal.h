#ifndef __BRCM_HAL__
#define __BRCM_HAL__


static __inline__ void PRC_CPU_NOP(int count)
{
    volatile int i = 0;
    while( i<count ) {
		i++;
    }
}

static __inline__ void PRC_CPU_64_WRITE(unsigned int addr, unsigned long long val)
{
	*(volatile unsigned long long*)(addr) = val;
}

static __inline__ unsigned long long PRC_CPU_64_READ(unsigned int addr)
{
	return *(volatile unsigned long long *)(addr);
}



static __inline__ void PRC_CPU_WRITE(unsigned long addr,unsigned long val)
{

   *(volatile unsigned long *)addr = val;
}

static __inline__ void PRC_CPU_WRITE_16(unsigned long addr,unsigned short val)
{
   *(volatile unsigned long *)addr = val;
}


static  __inline__ unsigned long PRC_CPU_READ(unsigned long addr)
{
   return *(volatile unsigned long *)addr;
}

static __inline__ unsigned long PRC_CPU_READ_16(unsigned long addr)
{
   return *(volatile unsigned short *)addr;
}

/* The following defines are used to access the MCTU for getting timestamps */
#define MCTU_OFFSET				    0xBE0D8000
#define MCTU_UPDATE_REGS			MCTU_OFFSET
#define MCTU_READ_MCC				MCTU_OFFSET + 4
#define MCTU_READ_MSLC			MCTU_OFFSET + 8
#define MCTU_READ_MFC				MCTU_OFFSET + 12


#endif
