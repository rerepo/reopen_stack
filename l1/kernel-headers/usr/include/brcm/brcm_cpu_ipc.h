#ifndef BRCM_CPU_IPC_H
#define BRCM_CPU_IPC_H

#define MCPU_IN_ORDER  							0x0 
#define MCPU_WAIT           					0x0
#define MCPU_OUT_OF_ORDER						0x1
#define MCPU_NOWAIT				                0x2

#define NUM_OF_RESERVED_PORTS					10
#define FIRST_USER_PORT_ID						NUM_OF_RESERVED_PORTS
#define MAX_NUM_OF_PORTS						32


#define CHARDEV_LOGICAL_OPEN					0x10
#define CHARDEV_OPENED							0x11
#define CHARDEV_CLOSED							0x22

#define IOCTL_BRCM_CHARDEVOPS_SET_BUFF			0x1111
#define IOCTL_BRCM_CHARDEVOPS_SET_BLOCK			0x1
#define IOCTL_BRCM_CHARDEVOPS_SET_NONBLOCK		0x0


#define MCPU_IPC_MAX_MSG_SIZE           256

#define IPC_OPEN_PORT		 	0
#define IPC_CLOSE_PORT			1
#define IPC_SEND_MSG			2
#define IPC_RECV_MSG			3	
#define IPC_SEND_MULTI			4
#define IPC_RECV_MULTI			5	
#define IPC_UNBLOCK_PORT		6

typedef struct {
        int                             port;
        unsigned int                    size;
        void                            *pPayload;
        int                             flags;
}mcpu_ipc_msg;

#ifdef __KERNEL__
static int __init bcm617xx_IPC_init_module(void);
static void __exit bcm617xx_IPC_cleanup(void);
#endif /*__KERNEL__ */


#endif /*BRCM_CPU_IPC_H*/

