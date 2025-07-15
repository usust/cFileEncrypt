//
// Created by lyu on 10/12/24.
//

#include "xor.h"

#include <stdio.h>
#include "../share.h"

#define XOR_KEY 0xAC
int byte_xor_byte_encrypt(char *encryted, int *encrypt_size, const char *decrypted, const int *decrypt_size) {
    printlnLog("%s current encryted used: %d\tdecrypted used: %d\n", "run byte_xor_byte_encrypt", *encrypt_size, *decrypt_size);
    int i = 0;
    for (; i < *decrypt_size; i++) {
        unsigned char uc = decrypted[i];
        // $$cusmake-server: byte_add_num::1$$
        ((unsigned char*)encryted)[i] = (unsigned char)(uc ^ XOR_KEY);
    }
    *encrypt_size = i;
    printlnLog("%s", "end byte_add_num\n");
    return 0;
}

int byte_xor_byte_decrypt(const char *encryted, const int *encrypt_size, char *decrypted, int *decrypt_size) {
#ifdef RUN_DECRYPT
    printlnLog("%s current encryted used: %d\tdecrypted used: %d\n",
    "run byte_xor_byte_decrypt", *encrypt_size, *decrypt_size);
    int i = 0;
    for (; i < *encrypt_size; i++) {
        unsigned char uc = encryted[i];
        // $$cusmake-server: byte_dec_num::1$$
        ((unsigned char*)decrypted)[i] = (unsigned char)(uc ^ XOR_KEY);
    }
    *decrypt_size = i;
    printlnLog("%s", "end byte_dec_num\n");
#endif
    return 0;
}
