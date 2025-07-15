//
// Created by lyu on 6/26/24.
//

#include "factory.h"

#include <stdio.h>
#include <stdlib.h>


#include "files/fileio.h"
#include "share.h"

int init_factory(struct Factory* factory, int mode) {
    printlnLog("[+] start init encrypt/decrypt factory\n");
    factory->encrypted = malloc(_100MB_);
    factory->decrypted = malloc(_100MB_);
    printlnLog("  [*] encrypt buffer size (bytes): %d\n", _100MB_);
    printlnLog("  [*] create decrypt buffer size  (bytes): %d\n", _100MB_);
    factory->flow_line_count = 0;
    factory->mode = mode;
    return 0;
}

void clean_factory(struct Factory* factory) {
    if (factory->encrypted != NULL) {
        free(factory->encrypted);
        factory->encrypted = NULL;
    }
    if (factory->decrypted != NULL) {
        free(factory->decrypted);
        factory->decrypted = NULL;
    }
}

int load_init_data(struct Factory *factory, const char* filename) {
    factory->decrypted_used_size = read_file(filename, factory->decrypted);
    factory->encrypted_used_size = read_file(filename, factory->encrypted);
    return 0;
}

int add_encryt_floor(struct Factory* factory, PFN_ENCRYPT encrypt_func, PFN_DECRYPT decrypt_func) {
    if (factory->flow_line_count+1 <= 10) {
        factory->applied_encrypt_floor[factory->flow_line_count].encrypt = encrypt_func;
        factory->applied_encrypt_floor[factory->flow_line_count].decrypt = decrypt_func;
        factory->flow_line_count++;
        return 0;
    }
    return -1;
}


int do_work(const char* file_path, struct Factory *factory) {
    for (int i = 0; i < factory->flow_line_count; i++) {
        if (i > 0) {
            ready_do_next(factory);
        }
        if (factory->mode == ENCRYPT_MODE) {
            factory->applied_encrypt_floor[i].encrypt(
                factory->encrypted, &factory->encrypted_used_size,
                factory->decrypted, &factory->decrypted_used_size);
        } else if (factory->mode == DECRYPT_MODE) {
            factory->applied_encrypt_floor[factory->flow_line_count-1-i].decrypt(
                factory->encrypted, &factory->encrypted_used_size,
                factory->decrypted, &factory->decrypted_used_size);
        }
    }
    return 0;
}

void ready_do_next(struct Factory *factory) {
    // exchange the decrypt and the encrypt
    char* dec_ptr = factory->decrypted;
    const int dec_used_size = factory->decrypted_used_size;
    factory->decrypted = factory->encrypted;
    factory->decrypted_used_size = factory->encrypted_used_size;
    factory->encrypted = dec_ptr;
    factory->encrypted_used_size = dec_used_size;
}
