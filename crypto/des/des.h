#ifndef __DES_H__
#define __DES_H__

#define ENCRYPT_MODE       		0
#define DECRYPT_MODE        	1

int Do_DES(char* strSrc, char* strKey, char* strDest, char flag);

int alg_des(unsigned char *dst, unsigned char *src, unsigned char *key, int mode);
int alg_3des(unsigned char *dst, unsigned char *src, unsigned char *key, int mode);
int alg_3des_cbc(unsigned char *dst, unsigned char *src, unsigned char *key,
                 unsigned char *iv, unsigned int len, int mode);

#endif
