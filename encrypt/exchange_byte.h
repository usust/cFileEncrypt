//
// Created by lyu on 7/22/24.
//

#ifndef EXCHANGE4BYTE_H
#define EXCHANGE4BYTE_H

/**
 * !!! Dont use to encrypt the flag file. !!!
 * every two bytes are swapped with each other. for example, 0x34 0xFF -> 0xFF 0x34
 * at the end, the rest doesn't change.
 * @param encryted
 * @param encrypt_size 
 * @param decrypted 
 * @param decrypt_size 
 * @return 
 */
int enExchangeByte(char *encryted, int *encrypt_size, const char *decrypted, const int *decrypt_size);
int deExchangeByte(const char* encryted, const int* encrypt_size, char* decrypted, int* decrypt_size);

#endif //EXCHANGE4BYTE_H
