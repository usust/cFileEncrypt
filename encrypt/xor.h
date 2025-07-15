//
// Created by lyu on 10/12/24.
//

#ifndef XOR_H
#define XOR_H
// typedef int(*PFN_ENCRYPT)(char*, int*, const char*, const int*);
// typedef int(*PFN_DECRYPT)(const char*, const int*, char*, int*);
int byte_xor_byte_encrypt(char* encryted, int* encrypt_size, const char* decrypted, const int* decrypt_size);
int byte_xor_byte_decrypt(const char* encryted, const int* encrypt_size, char* decrypted, int* decrypt_size);

#endif //XOR_H
