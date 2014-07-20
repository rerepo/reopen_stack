#ifndef BRCM_MMAP_IPC_H
#define BRCM_MMAP_IPC_H

#define BRCM_MMAP_IPC_MAJOR 	237
#define BRCM_MMAP_IPC_NUM_OF_INSTANCES  10

#define MMAP_IPC_GET_BUFFER_SIZE     0 
#define MMAP_IPC_GET_BUFFER_OFFSET   1
#define MMAP_IPC_GET_BUFFER_PHYSICAL 2
#define MMAP_IPC_FLUSH_CACHE		 3
#define MMAP_IPC_ALLOCATE_MEMORY     4
#define MMAP_IPC_INV_CACHED_BUFFER	 6
#define MMAP_IPC_FLUSH_CACHE_MULTI	 7
#define MMAP_IPC_INV_CACHED_BUFFER_MULTI	 8
#define MMAP_IPC_GET_BUFFER_VIRTUAL	 9


#ifdef __KERNEL__

#define BRCM_MMAP_IPC_SHARED_MEM_END			0xB0000000
#define BRCM_MMAP_IPC_SHARED_MEM_VADDR_BASE		0x40000000


unsigned long mmap_shared_allocate_mem(unsigned long idx, unsigned long len, unsigned long cached);
int mmap_shared_get_buf_size(unsigned long idx);     		
int mmap_shared_get_offset(  unsigned long idx);       	
int mmap_shared_get_physical(unsigned long idx);     		
int mmap_shared_get_virtual( unsigned long idx);     		
int mmap_shared_flush(     unsigned long addr, unsigned long len, unsigned long flags);		
int mmap_shared_invalidate(unsigned long addr, unsigned long len, unsigned long flags);	
int mmap_shared_flush_multi(     struct iovec *iov, unsigned long iovitems, unsigned long flags);		
int mmap_shared_invalidate_multi(struct iovec *iov, unsigned long iovitems, unsigned long flags);	



#ifdef __BRCM_MMAP_IPC_INTERNAL__
#define EXTERN 
static int brcm_mmap_ipc_mmap(struct file * filp, struct vm_area_struct * vma);
static int brcm_mmap_ipc_open (struct inode *inode, struct file *file);

#else
#define EXTERN extern
#endif /* __BRCM_MMAP_IPC_INTERNAL__ */

#endif /* __KERNEL__ */



#undef EXTERN
#endif
