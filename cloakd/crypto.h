#ifndef DAEDRA_CRYPTO_H
#define DAEDRA_CRYPTO_H

#include <linux/module.h>

/*
 * NOTE:
 * This function allocates memory for decrypted payload and returns a pointer to it.
 * The caller is responsible for memory deallocation!
 */
unsigned char * 
authenticate_and_decrypt(unsigned char *);

unsigned char *
decrypt_input(unsigned char *);

#endif
