#ifndef PERCELLO_AEAD_H
#define PERCELLO_AEAD_H

#include "brcm_ipsec.h"


#define BRCM_MAX_KEY_SIZE   512 

struct brcm_esp_ctx {
	
	u8							cipher_key[BRCM_MAX_KEY_SIZE];  
	u8							auth_key[BRCM_MAX_KEY_SIZE];
	u8							key[BRCM_MAX_KEY_SIZE];
	u8							iv[AES_BLOCK_SIZE];


	unsigned int				cipher_keylen;
	unsigned int				auth_keylen;
	unsigned int				digest_size;
	unsigned int				keylen;
    unsigned int				iv_len;
	sadb_t						*sadb;
};



#endif

