#ifndef PROCFS_UTIL_H
#define PROCFS_UTIL_H
#include <linux/seqlock.h>

#define VP (void *)

/* Type is 16 bits. High 8 bits are type of entry */
#define   PFS_MAIN			1<<8
#define   PFS_DIR			1<<9
#define   PFS_READ			1<<10
#define   PFS_WRITE			1<<11
#define   PFS_RW  			1<<12
/* low 8 bits are for read/write formating */
#define   PFS_LU			1  /* unsigned long */
#define   PFS_STR			2  /* string */
#define   PFS_LLU			4  /* long long unsigned */
#define   PFS_VLU			8  /* long unsigned from array*/

typedef struct {
  seqlock_t 		seq_lock;
  spinlock_t 		spin_lock;
} procfs_locks_t;


typedef int (*f_t)(char *pFmt, ...);
typedef int (*pfs_r_t)(char *page, char **start, off_t off,int count, int *eof,void *data);
typedef int (*pfs_w_t)(struct file* file, const char* buffer, unsigned long count, void* data);

typedef struct {
	pfs_r_t		read_proc;
	pfs_w_t		write_proc;
} rw_funcs_t;


typedef struct {
  char						name[20];
  struct proc_dir_entry 	*proc_dir;		
  unsigned char 			parent_idx;
  unsigned short 			type; 
  unsigned long  			len;
  void 						*arg;
  f_t 						function;
  char 						frmt[10];
  procfs_locks_t 			*lock;
} procfs_entry_t;


#ifdef __PROCFS_UTIL__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int procfs_write_entry_int(struct file* file, const char* buffer, unsigned long count, void* data);
EXTERN int procfs_write_entry(struct file* file, const char* buffer, unsigned long count, void* data);
EXTERN int procfs_read_entry_int(char *page, char **start, off_t off,int count, int *eof,void *data);
EXTERN void procfs_build_entries(procfs_entry_t array[],unsigned short len,procfs_locks_t *locks);
EXTERN int procfs_read_entry(char *page, char **start, off_t off,int count, int *eof,void *data);
EXTERN void procfs_remove_entries(procfs_entry_t array[],unsigned short len);

#undef EXTERN
#endif

