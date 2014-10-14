#ifndef DAEDRA_CRYPTO_H
#define DAEDRA_CRYPTO_H

#include <linux/module.h>

/*
 * NOTE:
 * This function allocates memory for decrypted payload and returns a pointer to it.
 * The caller is responsible for memory deallocation!
 */
u8* authenticate_and_decrypt(const u8* const);

u8* decrypt_input(const u8* const);

#endif
