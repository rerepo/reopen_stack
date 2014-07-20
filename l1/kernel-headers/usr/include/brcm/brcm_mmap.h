#ifndef BRCM_MMAP_H
#define BRCM_MMAP_H

#define BRCM_MMAP_MAJOR 	240
#define BRCM_MMAP_NAME 	"brcm_mmap"

#define BRCM_MMAP_NUM_OF_INSTANCES  10

#define GET_BUFFER_SIZE     0 
#define GET_BUFFER_OFFSET   1
#define GET_BUFFER_PHYSICAL 2
#define FLUSH_CACHE			3
#define ALLOCATE_MEMORY     4
#define UV_TO_K     		5
#define FLUSH_CACHED_BUFFER 6
#define INV_CACHED_BUFFER	7

#ifdef __KERNEL__
typedef struct {
  struct list_head 		free_list;
  struct list_head 		allocated_list;
} mem_buffer_list_t;

typedef struct {
  struct list_head 		buf_ptr;
  unsigned long 		size;
  unsigned long 		start;
} mem_buffer_t;




#ifdef __BRCM_MMAP_INTERNAL__
#define EXTERN 
static int brcm_mmap_mmap(struct file * filp, struct vm_area_struct * vma);
static int brcm_mmap_open (struct inode *inode, struct file *file);
static int __init brcm_mmap_init_module (void);
static void __exit brcm_mmap_cleanup_module (void);

#else
#define EXTERN extern
#endif /* __BRCM_MMAP_INTERNAL__ */
EXTERN unsigned long convert_uvirt_to_kva(unsigned long va);
#endif /* __KERNEL__ */



#undef EXTERN
#endif
