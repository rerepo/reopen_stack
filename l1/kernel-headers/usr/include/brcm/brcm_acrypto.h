
#ifndef __BRCM_ACRYPTO__H_
#define __BRCM_ACRYPTO__H_

#include "brcm_acrypto_AES.h"
#include "brcm_acrypto_SHA.h"

#define PRC_ENCRYPT				1
#define PRC_DECRYPT				0

#define BRCM_MAX_KEY_SIZE		512 
#define MAX_IPSEC_REQS			300

struct brcm_esp_ctx {
	
	u8							cipher_key[BRCM_MAX_KEY_SIZE];  
	u8							auth_key[BRCM_MAX_KEY_SIZE];
	u8							key[BRCM_MAX_KEY_SIZE];
	u8							iv[AES_BLOCK_SIZE];


	unsigned int				cipher_keylen;
	unsigned int				auth_keylen;
	unsigned int				digest_size;
	unsigned int				keylen;
	unsigned int				keycode;
    unsigned int				iv_len;
};


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
		struct sk_buff			*the_skb;	
		struct brcm_esp_ctx     *ctx;
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

int brcm_acrypto_aes_init (void);
void brcm_acrypto_aes_cleanup (void);

int cbc_aes_set_key(prc_ipsec_t *req, const u8 *in_key,unsigned int key_len);
int cbc_aes_encrypt(prc_ipsec_t *req);
int cbc_aes_decrypt(prc_ipsec_t *req);
int brcm_sha1_final(prc_ipsec_t* req, u8 *out);

void poll_aes(prc_ipsec_t *req);
void poll_sha(prc_ipsec_t *req, u8* out);

#endif /*__BRCM_ACRYPTO__H_*/