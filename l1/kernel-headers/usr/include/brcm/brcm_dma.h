#ifndef BRCM_DMA_H
#define BRCM_DMA_H

#define DMA_MULTI					0
#define DMA_GET_LOG					1

#define	MAX_DMA_LOG_STR				200
#define	DMA_LOG_MAX_IDX				1000

// Flag masks
#define DMA_COPY_FLAGS_NO_WAIT		0x1
#define DMA_COPY_FLAGS_ALL_DMA		0x2
#define DMA_COPY_FLAGS_STATIC_CHAN	0x4
#define DMA_COPY_FLAGS_FAST_COPY	0x8
#define DMA_COPY_FLAGS_NO_WAIT_HP   0x10

//Flag values
#define DMA_WAIT					0x1
#define DMA_NO_WAIT					0x0
#define DMA_NO_WAIT_HP				0x10

#define DMA_USE_STATIC_CHAN			0x1

/* The channel to use when requesting static channel */
#define DMA_STATIC_CHANNEL_NUM		0 /* lowest priority, for SNOW, etc. */

#ifdef __KERNEL__
#define U32 u32
#define U16 u16
#else
#define U32 unsigned long
#define U16 unsigned short
#endif


typedef int (*copy_routine_t)(void *dst,void *src,int len);

typedef struct 
{
   unsigned char		*source;
   unsigned char		*destination;
   unsigned long        length;	
} PRC_DMA_ELEMENT;

typedef struct 
{
   unsigned long		n_elements;
   PRC_DMA_ELEMENT		*dma_element; 
} PRC_DMA_COPY;



#define	MAX_MAPPINGS				10
#define	REQUESTS_FIFO_SIZE			100
#define MAX_ELEMENTS_IN_REQ			256
#define	DMA_REQUEST_TIMEOUT			1000
#define MAX_DMA_CHANNELS			4
#define DMA_MAX_ELEMENTS			256

#define DMA_DDR_CHAN				2 // Same as for UL
#define DMA_UL_CHAN					2
#define DMA_DL_CHAN					3
#define DMA_DDR_CHAN_HP				3 

typedef struct 
{
   U32					     flags;
   int					     index;
   int					     q_id;
   PRC_DMA_COPY			*copy_list;
} userspace_dma_request_t;

#ifdef __KERNEL__

typedef struct 
{
	struct list_head	list_element;
	PRC_DMA_ELEMENT		element;
	copy_routine_t		copy_routine;
} dma_transfer_element_t;



typedef struct 
{
	struct list_head	elements_list;
	int					      num_elements;
} dma_transfer_list_t;

typedef struct 
{
   U32					flags;
   int					index;
   int					q_id;
   PRC_DMA_COPY			*copy_list;
   dma_transfer_list_t  		memcopy_list;
   dma_transfer_list_t  		dmacopy_list;
} dma_request_t;



typedef struct
{
   struct list_head		list;
   dma_request_t		dma_request;
   wait_queue_head_t	wait_queue;
   int					wait_flag;
   unsigned int			rt_prio;
} queue_entry_t;

typedef struct 
{
	struct list_head	mappings_list;
	u32					physical_base;
	u32					virtual_base;
	u32					virtual_max;
	long				offset;
	u32					length;
	u32					pid;

} virtual_mapping_t;

#ifdef __BRCM_DMA_INTERNAL__
int			dma_driver_copy_to_user(void *dst,void *src int len);
int			dma_driver_copy_from_user(void *dst,void *src, int len);
int			dma_driver_memcpy(void *dst,void *src int len);
static int	copy_dma_elements(void);
static int	copy_memcpy_elements(void);

#define EXTERN 
#else
#define EXTERN extern
#endif /* __BRCM_DMA_INTERNAL__ */

EXTERN int brcm_dma_copy(dma_request_t *dma_request);
EXTERN int brcm_dma_copy_single(void *dst, void *src, int len);

/* DMA functions */
#undef EXTERN


#endif /* __KERNEL__ */


#endif
