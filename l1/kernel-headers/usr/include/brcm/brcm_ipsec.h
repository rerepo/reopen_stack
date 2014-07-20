#ifndef PERCELLO_IPSEC_H
#define PERCELLO_IPSEC_H

#include "brcm_ocf_SHA.h"
#include "brcm_ocf_AES.h"
#include <linux/skbuff.h>
#include <brcm_ipsec.h>
#include <linux/tcp.h>
#include <net/xfrm.h>
#include <linux/ip.h>
#include <linux/rtnetlink.h>
#include <asm/r4kcache.h>


#define PRC_ENCRYPT 1
#define PRC_DECRYPT 0



#define DECRYPT_OP				(!PRC_DECRYPT)/* no good reason. When wrote the code i didn't noticed that we have those PRC_XXCRYPT definitions */
#define ENCRYPT_OP				(!PRC_ENCRYPT)
#define PRC_NULL_OP					777
#define PRC_FASTSOCK_TX				555

#define IPSEC_MACHINE_0			0
#define IPSEC_MACHINE_1			1
#define IPSEC_MACHINE_OLD		2

#define NO_WAIT_FOR_RESULTS		0
#define WAIT_FOR_RESULTS		1

#define CPY_IN_TXT_NONE			0
#define CPY_IN_TXT				1

#define MAX_IPSEC_REQS			300

#define HW_MAX_FRAGS_PER_PCKT   8

#define NUM_OF_MACHINES	2
#define MAX_NUM_OF_PKTS 10

#define 		MODE_ESP					0
#define 		MODE_ESP_IN_UDP		1
#define 		MODE_UDP					2
#define 		MODE_NOT_ESP			0xF

static inline void flush_and_invalidate_area(u32 start_addr, u32 length)
{
    unsigned long start = start_addr;
    unsigned long end = (start_addr + length + 31) & 0xffffffe0;
  
  	for( ; start < end; start +=32)
	  {
		 	flush_dcache_line(start);
			invalidate_dcache_line(start);
	  }	
			
	  start = start_addr;
	  end = (start_addr + length + 127) & 0xffffff80;
	  for( ; start < end; start +=128)
	  {
	 	  flush_scache_line(start);
		  invalidate_scache_line(start);
	  } 	
}




/**
 * ================================================================================================= 
 *  Flush a given address range to physical memory
 * 
 * ================================================================================================= 
 */
static inline void flush_descriptor(u32 start_addr, u32 length)
{
	 u32  start = start_addr;
	 u32  end = (start + length + 31) & 0xffffffe0;

   for( ; start < end; start +=32)
	 {
			flush_dcache_line(start);//L1 Dcache line size is 32 bytes both at CPUH and CPUL.
	 }	
  start = start_addr;
	end = (start + length + 127) & 0xffffff80;
	for( ; start < end; start +=128)
	{
			flush_scache_line(start);//scache line size is 128 bytes both at CPUH and CPUL.
	}		
	__asm__ __volatile__("sync"); 
}	

 
static inline int determine_esp_mode(struct iphdr *iph, struct udphdr *udph,__u8	*udpdata)
{
	__be32							*udpdata32;
 	int									ret = MODE_NOT_ESP;
 	
 	if(iph->protocol == 0x11)
 	{
  	if((ntohs(udph->dest) == 4500) && (ntohs(udph->source) == 4500))
  	{
	  		udpdata32 = (__be32 *)udpdata;
	  		if( ( *udpdata != 0xFF) && ((*udpdata32)) )
	  		{
	  			ret = MODE_ESP_IN_UDP;
	  		}
	  }
	}
	else
	{
		if(iph->protocol == 0x32)
		{
					ret = MODE_ESP;
		}
	}
	return ret;
}



typedef struct sadb{
	u32 spi_base;
	u32 daddr;
	u32 cryptomode;
	u32 reserved1;
	u32 reserved2;
	u32 cipher[8];
	u32 iv[4];
	u32 hmac[32];
	u32 hmacoffset;
	struct sadb *prev;
	struct sadb *next;
} sadb_t;

typedef struct {
	u32 spi;
	u32 sadb_addr;
	u32 daddr;
	u32 digest_addr;
	u32 flags;
	u32 iv0;
	u32 iv1;
	u32 iv2;
	u32 iv3;
} desc_t;

typedef struct {
        u8*   					hmac_key;
        u8*   					cipher_key;
		u8*   					iv;
        u8*   					cipher_src;
        u8*   					hmac_src;
        u8*   					dst;
		u8*						packet_digest;
		u32   					store_digest[/*20*/5];
		u8*						digest;
		int  					cipher_len;
		int   					hmac_len;
		int	  					enc_dec;
		struct aead_request 	*areq;
		struct xfrm_state		*x; 
		struct scatterlist 		*sg_hmac_src;
		struct scatterlist 		*sg_cipher_src;
		struct scatterlist 		*sg_cipher_dst;
		struct napi_struct		*napi;
		int						rx_coe;
		struct sk_buff			*the_skb;	
		struct brcm_esp_ctx     *ctx;
		u32						fastsock_id;
		desc_t					desc;//dma must follow this field
		u32						dma[20];//max 8 frags
		u32						hw_unique_id;
} prc_ipsec_t;

static __inline void printer(char *msg,unsigned char *key,int len)
{
	int i;
	unsigned char *c;
	printk("%s:",msg);
	for(i=0,c=key;i<len;i++,c++)
		printk("%02x",*c);
	printk("\n");
}


static __inline int sg_count(struct scatterlist *src,struct scatterlist **last_sg)
{
	
	int										frags;
		struct scatterlist 	*sg;
	  
	sg = src;
	*last_sg = sg;
		frags = 0;
		
	while(sg) 
		{
			frags++;
		*last_sg = sg; 
			sg = sg_next(sg);
		}
		return frags;
}


static __inline void copy_from_sg_to_hw(struct scatterlist *src,void *dst,int nbytes)
{

		int									count;
		int									bytes;
	  struct scatterlist 	*sg;
	  
		sg=src;
		count=0;
		bytes = nbytes ;
		while (bytes>0) 
		{
			if(sg)
			{
					memcpy((void*)dst+count,sg_virt(sg),(sg->length > bytes ? bytes: sg->length));
					bytes -= sg->length;
					count+=sg->length;
					if (bytes>0)
						sg = sg_next(sg);
			}
			else
				bytes=0;
		}
}

static __inline void copy_from_hw_to_sg(struct scatterlist *dst,void *src,int nbytes)
{

		int									count;
		int									bytes;
	  struct scatterlist 	*sg;
	  
		sg=dst;
		count=0;
		bytes = nbytes ;
		while ((bytes>0) && (sg))
		{
			memcpy((void*)sg_virt(sg),src+count,(sg->length > bytes ? bytes : sg->length));
			bytes -= sg->length;
			count+=sg->length;
			if (bytes>0)
				sg = sg_next(sg);
		}
}



#ifdef __PERCELLO_IPSEC_INTERNAL__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN void   brcm_ipsec_encrypt_no_frag(prc_ipsec_t *req, int machine);
EXTERN void   brcm_ipsec_decrypt_no_frag(prc_ipsec_t *req, int machine);
EXTERN void   brcm_ipsec_decrypt(prc_ipsec_t *req, int machine);
EXTERN void   brcm_ipsec_encrypt(prc_ipsec_t *req, int machine);
EXTERN int brcm_ipsec_init(void);


#endif
