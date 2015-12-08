#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des/des.h"

#define DEBUG_MODE  0

#if DEBUG_MODE
#define dbg(fmt, arg...)        printf((char *)fmt, ##arg)
#else
#define dbg(fmt, arg...)        do {}while(0)
#endif

static void dbg_buf(const char *name, unsigned char *buf, unsigned int len)
{
#if DEBUG_MODE
	unsigned char data[2 * len + 1];
	unsigned char tmp;
	int i;
	
	printf("%s", name);
	
	for (i = 0; i < len; i++) {
		tmp = (buf[i] & 0xF0) >> 4;
		data[i * 2] = (tmp > 9) ? tmp - 10 + 'A' : tmp + '0';
		tmp = buf[i] & 0x0F;
		data[i * 2 + 1] = (tmp > 9) ? tmp - 10 + 'A' : tmp + '0'; 
	}
	data[2 * len] = 0;
	
	printf("%s\n", data);
#endif
}

static int t_des(void)
{
    int ret = 0;
    unsigned char plain[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
    unsigned char key[8] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37 };
    unsigned char cipher[8] = { 0x76, 0x0e, 0xec, 0xc7, 0x31, 0x46, 0xaf, 0x6c };
    unsigned char tmp[8] = { 0 };

    dbg_buf("key : ", key, sizeof(key));
    dbg_buf("plaintext : ", plain, 8);
    dbg("encryption\n");
    alg_des(tmp, plain, key, ENCRYPT_MODE);
    dbg_buf("cipher : ", tmp, 8);
    if (memcmp(tmp, cipher, 8) != 0)
        ret += 0x1;
    dbg("decryption\n");
    alg_des(tmp, cipher, key, DECRYPT_MODE);
    dbg_buf("plaintext : ", tmp, 8);
    if (memcmp(tmp, plain, 8) != 0)
        ret += 0x10;

    return ret;
}

static int t_3des(void)
{
    int ret = 0;
    unsigned char plain[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE7 };
    unsigned char key[24] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
        0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
        0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67 };
    unsigned char cipher[8] = { 0xDE, 0x0B, 0x7C, 0x06, 0xAE, 0x5E, 0x0E, 0xD5 };
    unsigned char tmp[8] = { 0 };

    dbg_buf("key : ", key, sizeof(key));
    dbg_buf("plaintext : ", plain, 8);
    dbg("encryption\n");
    alg_3des(tmp, plain, key, ENCRYPT_MODE);
    dbg_buf("cipher : ", tmp, 8);
    if (memcmp(tmp, cipher, 8) != 0)
        ret += 0x1;
    dbg("decryption\n");
    alg_3des(tmp, cipher, key, DECRYPT_MODE);
    dbg_buf("plaintext : ", tmp, 8);
    if (memcmp(tmp, plain, 8) != 0)
        ret += 0x10;

    return ret;
}


static int test_des(void)
{
    int ret = 0;

    printf("\n");
    ret = t_des();
    if (ret != 0) {
        printf("des algo : Error ret=%x\n", ret);
    } else {
        printf("des algo : OK\n");
    }

    printf("\n");
    ret = t_3des();
    if (ret != 0) {
        printf("3des algo : Error ret=%x\n", ret);
    } else {
        printf("3des algo : OK");
    }
    printf("\n");

    return ret;
}

int main(int argc, char **argv)
{
    test_des();

    return 0;
}

