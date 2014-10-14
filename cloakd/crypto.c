#include <linux/slab.h>
#include <linux/string.h>
#include "crypto.h"

u8*
authenticate_and_decrypt(const u8* const encrypted_input)
{
    /**************************************************************************
     * VERY BIG TODO: Implement crypto !!!
     *************************************************************************/
    return decrypt_input(encrypted_input);
}

u8*
decrypt_input(const u8* const encrypted_input)
{
    /*************************************************************************
     * NOTE: Since crypto is not implemented yet, just copy to decrypted_input 
     *       whatever we get as input (as if pretending that we have decrypted 
     *       the input)
     * TODO: When crypto is put in place, revisit kmalloc and memcpy 
     ************************************************************************/

    u8 *decrypted_input;

    decrypted_input = kmalloc(strlen(encrypted_input), GFP_KERNEL);
    printk(KERN_INFO "crypto: Allocated %zu bytes\n", ksize(decrypted_input));

    if (!decrypted_input)
        return decrypted_input;

    memcpy(decrypted_input,
           encrypted_input /* just copy whatever we get as input */,
           ksize(decrypted_input));
    return decrypted_input;
}
