#ifndef BRCM_FRAME_CAP_H
#define BRCM_FRAME_CAP_H

#define BRCM_FRAME_CAP_MAJOR 	241
#define BRCM_FRAME_CAP_NAME 	"brcm_frame_capture"




#define FC_GET_BUFFER_SIZE     0 
#define FC_GET_BUFFER_OFFSET   1
#define FC_GET_BUFFER_PHYSICAL 2
#define FC_FLUSH_CACHE		   3
#define FC_ALLOCATE_MEMORY     4

#ifdef __KERNEL__

#ifdef __BRCM_FRAME_CAP_INTERNAL__
#define EXTERN 
static int		frame_capture_cmd_demux(unsigned long cmd, unsigned long arg,void *arg1);
static int		brcm_frame_capture_open (struct inode *inode, struct file *file);
static int		brcm_frame_capture_mmap(struct file * filp, struct vm_area_struct * vma);
static int		__init brcm_frame_capture_init_module (void);
static void		__exit brcm_frame_capture_cleanup_module (void);

#else
#define EXTERN extern
#endif /* __BRCM_FRAME_CAP_INTERNAL__ */
#endif /* __KERNEL__ */

#undef EXTERN
#endif
