//
// Created by lyu on 7/22/24.
//

#include "exchange_byte.h"

#include <stdio.h>
#include "../share.h"

int enExchangeByte(char *encryted, int *encrypt_size, const char *decrypted, const int *decrypt_size) {
    printlnLog("%s current encryted used: %d\tdecrypted used: %d\n", "run enExchangeByte", *encrypt_size, *decrypt_size);

    int word_size = *decrypt_size / 2;
    for (int i = 0; i < word_size*2; i += 2) {
        encryted[i] = decrypted[i+1];
        encryted[i+1] = decrypted[i];
    }
    for (int i = word_size*2; i < *decrypt_size%2; i++) {
        encryted[i] = decrypted[i];
    }
    *encrypt_size = *decrypt_size;

    printlnLog("%s", "end enExchangeByte\n");
    return *encrypt_size;
}

int deExchangeByte(const char* encryted, const int* encrypt_size, char* decrypted, int* decrypt_size) {
#ifdef RUN_DECRYPT
    printlnLog("%s current encryted used: %d\tdecrypted used: %d\n",
    "run deExchangeByte", *encrypt_size, *decrypt_size);
    int word_size = *encrypt_size / 2;
    for (int i = 0; i < word_size*2; i += 2) {
        decrypted[i] = encryted[i+1];
        decrypted[i+1] = encryted[i];
    }
    for (int i = word_size*2; i < *encrypt_size%2; i++) {
        decrypted[i] = encryted[i];
    }
    *decrypt_size = *encrypt_size;

    printlnLog("%s", "end deExchangeByte\n");
#endif
    return *decrypt_size;
}