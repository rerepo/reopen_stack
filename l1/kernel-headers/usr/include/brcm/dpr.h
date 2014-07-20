#ifndef DPR_H
#define DPR_H


#define SIZE_OF_DPR 2048
#define DPR_DSP_WORD_TYPE unsigned short 
#define DPR_DSP_WORD_SIZE  sizeof(DPR_DSP_WORD_TYPE)

typedef enum
{
   L1_TO_DSP_TOTAL_DATA_LENGTH = 0,
   L1_TO_DSP_MORE_MESSAGES        ,  
   L1_TO_DSP_NUM_OF_MESSAGES      ,
   DSP_TO_L1_TOTAL_DATA_LENGTH    ,
   DSP_TO_L1_MORE_MESSAGES        ,
   DSP_TO_L1_NUM_OF_MESSAGES      ,
   L1_TO_DSP_MSG_BUFFER           ,
   DSP_TO_L1_MSG_BUFFER           ,
   RESERVED1                      ,
   RESERVED2                      ,
   UL_DSP_TTI_CNTR                ,
   UL_L1_TTI_CNTR                 ,
   UL_HS_DPCCH_INDICATIONS        ,
   UL_TRCH_DYNAMIC_PARAMETERS     ,
   DL_DSP_TTI_CNTR                ,
   DL_L1_TTI_CNTR                 ,
   DL_HS_DYNAMIC_PARAMETERS       ,
   DL_REL99_DYNAMIC_PARAMETERS    ,
   DPR_NUM_OF_ELEMENTS

} DPR_ELEMENTS_enum;


typedef struct
{
  unsigned short			start;
  unsigned short			end;
  unsigned long				*base;
} DPR_ENTRY_t;


#ifdef __DPR_MODULE__


DPR_ENTRY_t dpr_elements[DPR_NUM_OF_ELEMENTS] =
{
/*  L1_TO_DSP_TOTAL_DATA_LENGTH    */ {0   ,0   ,&base},
/*  L1_TO_DSP_MORE_MESSAGES        */ {2   ,2   ,&base}, 
/*  L1_TO_DSP_NUM_OF_MESSAGES      */ {4   ,4   ,&base},
/*  DSP_TO_L1_TOTAL_DATA_LENGTH    */ {6   ,6   ,&base},
/*  DSP_TO_L1_MORE_MESSAGES        */ {8   ,8   ,&base},
/*  DSP_TO_L1_NUM_OF_MESSAGES      */ {10  ,10  ,&base},
/*  L1_TO_DSP_MSG_BUFFER           */ {12  ,512 ,&base},
/*  DSP_TO_L1_MSG_BUFFER           */ {0   ,248 ,&base_1},
/*  RESERVED1                      */ {760 ,768 ,&base},
/*  RESERVED2                      */ {768 ,1044,&base},
/*  UL_DSP_TTI_CNTR                */ {1196,1196,&base},
/*  UL_L1_TTI_CNTR                 */ {1197,1197,&base},
/*  UL_HS_DPCCH_INDICATIONS        */ {1198,1212,&base},
/*  UL_TRCH_DYNAMIC_PARAMETERS     */ {1213,1413,&base},
/*  DL_DSP_TTI_CNTR                */ {1414,1413,&base},
/*  DL_L1_TTI_CNTR                 */ {1415,1415,&base},
/*  DL_HS_DYNAMIC_PARAMETERS       */ {1416,1494,&base},
/*  DL_REL99_DYNAMIC_PARAMETERS    */ {1495,1536,&base}
};												 
												 
#else											 
extern DPR_ENTRY_t dpr_elements[DPR_NUM_OF_ELEMENTS];
#endif


#define DPR_L1_TO_DSP_BUF_SIZE (512-12) 
#define DPR_DSP_TO_L1_BUF_SIZE (760-512) 



static __inline__ void dpr_write(unsigned short dst_item,unsigned short offset,  void *src,unsigned short len)
{
  unsigned long dst = *(dpr_elements[dst_item].base) + ((dpr_elements[dst_item].start + offset ) * 2);
  memcpy((void *)dst,src,len*2); 

}

static __inline__ void dpr_write16(unsigned short dst_item,unsigned short offset,  void *src,unsigned short len)
{ 
   dpr_write(dst_item,offset,src,len);
}


static __inline__  DPR_DSP_WORD_TYPE  dpr_read(unsigned short item,unsigned short offset) 
{
  volatile unsigned long *t,addr;
  DPR_DSP_WORD_TYPE val; 
  addr = (dpr_elements[item].start + offset); 
  t = (unsigned long*)(*(dpr_elements[item].base) + ((addr/2)*4));
  if(addr &0x1)
    val = ((*t & 0xffff0000)>>16);
  else
    val = (*t & 0xffff);
  return val;

} 


static __inline__ void dpr_copy_from_dsp_buf(unsigned short *buf,unsigned short offset,unsigned short len)
{
   unsigned short end = dpr_elements[DSP_TO_L1_MSG_BUFFER].end;
   unsigned short start = dpr_elements[DSP_TO_L1_MSG_BUFFER].start + offset;
   
   if(start + len <= end)
   {
	   memcpy((void *)buf,(void *)(*(dpr_elements[DSP_TO_L1_MSG_BUFFER].base) + start*sizeof(unsigned short)),len*(sizeof(unsigned short)));
   }
   else
   {
      printk("len = %u offset = %u start = %u end = %u\n",len,offset,start,end);
      printk("Error copying data from DPR\n"); 
   }
} 

#endif
