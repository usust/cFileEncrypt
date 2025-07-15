//
// Created by lyu on 6/26/24.
//

#ifndef FACTORY_H
#define FACTORY_H

#define ENCRYPT_MODE 1
#define DECRYPT_MODE 2

typedef int(*PFN_ENCRYPT)(char*, int*, const char*, const int*);
typedef int(*PFN_DECRYPT)(const char*, const int*, char*, int*);


struct Factory {
    int mode;
    int current_floor;
    // buffer size max 1M
    char* encrypted;
    int encrypted_used_size;
    char* decrypted;
    int decrypted_used_size;

    int flow_line_count;
    struct EncryptFloor {
        PFN_ENCRYPT encrypt;
        PFN_DECRYPT decrypt;
    } applied_encrypt_floor[10];
};

int init_factory(struct Factory* factory, int mode);

void clean_factory(struct Factory* factory);

int load_init_data(struct Factory* factory, const char* filename);

int add_encryt_floor(struct Factory* factory, PFN_ENCRYPT encrypt_func, PFN_DECRYPT decrypt_func);

int do_work(const char* file_path, struct Factory* factory);

void ready_do_next(struct Factory* factory);
#endif //FACTORY_H
