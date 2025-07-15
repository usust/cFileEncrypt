//
// Created by lyu on 8/16/24.
//

#include "math_calc.h"
#include "stdio.h"
#include "../share.h"
#define MATH_CALC_KEY 0xAC
int byte_add_num(char *encryted, int *encrypt_size, const char *decrypted, const int *decrypt_size) {
    printlnLog("%s current encryted used: %d\tdecrypted used: %d\n",
    "run byte_add_num", *encrypt_size, *decrypt_size);
    int i = 0;
    for (; i < *decrypt_size; i++) {
        unsigned char uc = decrypted[i];
        // $$cusmake-server: byte_add_num::1$$
        ((unsigned char*)encryted)[i] = (unsigned char)(uc+MATH_CALC_KEY);
    }
    *encrypt_size = i;
    printlnLog("%s", "end byte_add_num\n");
    return 0;
}

int byte_dec_num(const char* encryted, const int* encrypt_size, char* decrypted, int* decrypt_size) {
#ifdef RUN_DECRYPT
    printlnLog("%s current encryted used: %d\tdecrypted used: %d\n",
    "run byte_dec_num", *encrypt_size, *decrypt_size);
    int i = 0;
    for (; i < *encrypt_size; i++) {
        unsigned char uc = encryted[i];
        // $$cusmake-server: byte_dec_num::1$$
        ((unsigned char*)decrypted)[i] = (unsigned char)(uc-MATH_CALC_KEY);
    }
    *decrypt_size = i;
    printlnLog("%s", "end byte_dec_num\n");
#endif
    return 0;
}