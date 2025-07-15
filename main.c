#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "share.h"
#include "mycstring.h"
#include "files/fileio.h"
#include "factory.h"
#include "encrypt/exchange_byte.h"
#include "encrypt/math_calc.h"
#include "encrypt/xor.h"

#define ENCRYPT_MODE 1
#define DECRYPT_MODE 2


void help() {
    printlnLog("\n\nencrypt and decrypt files.\n\n");
    printlnLog("Usage: <run mode> <file path...>\n");
    printlnLog("-E --encrypt: encrypt files\n");
    printlnLog("-D --decrypt: decrypt files\n");
    printlnLog("-I --input input directory\n");
    printlnLog("    * means all files in current directory.\n");
    printlnLog("-O --out: out directory\n");
    printlnLog("-R --running: not exit the process\n");
    printlnLog("Example 2: FileEncrypt -E -I ./in -O ./out\n");
    printlnLog("    encrypt all files in the in directory and output files into out directory.\n");
}

/**
 * 解析命令行参数
 * @param args 命令行参数个数
 * @param argv 命令行参数
 * @param params 保存解析后的参数结构体
 * @return
 *  0: success
 */
int parseCmdLine(int args, const char* argv[], struct StCmdParams* params) {
    if (args <= 1) {
        printlnLog("[E] missing parameter \n");
        return 99;
    }

    // set the default value of arguments.
    params->isExit = 0;
    // parsing
    for (int i = 1; i < args; ) {
        if (strcmp(argv[i], "-E") == 0 || strcmp(argv[i], "--encrypt") == 0) {
            params->mode = ENCRYPT_MODE;
            i++;
        } else if (strcmp(argv[i], "-D") == 0 || strcmp(argv[i], "--decrypt") == 0) {
            params->mode = DECRYPT_MODE;
            i++;
        } else if (strcmp(argv[i], "-I") == 0 || strcmp(argv[i], "--input") == 0) {
            params->inputDir = argv[i+1];
            i += 2;
        } else if (strcmp(argv[i], "-O") == 0 || strcmp(argv[i], "--out") == 0) {
            params->out = argv[i+1];
            i += 2;
        } else if (strcmp(argv[i], "-R") == 0 || strcmp(argv[i], "--running") == 0) {
            params->isExit = 1;
            i += 1;
        } else {
            printlnLog("[E] error parameter: %s\n", argv[i]);
            return 1;
        }
    }

    // check param: run mode.
    if (params->mode != ENCRYPT_MODE && params->mode != DECRYPT_MODE) {
        printlnLog("[E] not encrypt/decrypt mode \n");
        return 2;
    }

    // encrypt or decrypt
    if (params->inputDir == NULL) {
        printlnLog("[E] the input direction is empty\n");
        return 3;
    }

    return SUCCESS;
}

int main(const int args, const char* argv[]) {
    printlnLog("[+] start \n");
    struct StCmdParams stParam;
    if(SUCCESS != parseCmdLine(args, argv, &stParam)) {
        printlnLog("[!] parsed error \n");
        help();
        return -1;
    } else {
        printlnLog("[+] parsed the parameter \n");
    }

    printlnLog("\n");

    // 解析出所有文件
    // get all file path
    stParam.fileCount = getFileAbsPathListMP(stParam.inputDir, stParam.filenames, _1MB_);
    if (stParam.fileCount <= 0) {
        printlnLog("[E] read the direction error \n");
        return 1;
    } else {
        printlnLog("********************* found %d files.*********************\n", stParam.fileCount);
        char* fileNameIndex = stParam.filenames;
        for (int i = 0; i < stParam.fileCount; i++) {
            printlnLog("  [%d]%s\n", i+1, fileNameIndex);
            fileNameIndex += strlen(fileNameIndex)+1;
        }
        printlnLog("[+] read the direction success \n");
    }

    printlnLog("Run Mode: %d\n"
                      "Input Diectory: %s\n"
                      "File Count: %d\n"
                      "Out Dectory: %s\n"
                      "Is Exit: %d\n",
        stParam.mode, stParam.inputDir, stParam.fileCount, stParam.out, stParam.isExit);

    // 3. set encrypt factory
    struct Factory factory;
    init_factory(&factory, stParam.mode);

    /**
     * here ～～～
     * config encryption and decryption function
     */
    printlnLog("[append function] decrypt func: xor    decrypt func: xor\n");
    add_encryt_floor(&factory, byte_xor_byte_encrypt, byte_xor_byte_decrypt);
    printlnLog("[append function] decrypt func: enExchangeByte    decrypt func: deExchangeByte\n");
    add_encryt_floor(&factory, enExchangeByte, deExchangeByte);
    printlnLog("[append function] decrypt func: byte_add_num    decrypt func: byte_dec_num\n");
    add_encryt_floor(&factory, byte_add_num, byte_dec_num);

    char *p_cur_file_abs_path = stParam.filenames;
    for (int i = 0; i < stParam.fileCount; i++) {
        printlnLog("doing %s\n", p_cur_file_abs_path);
        load_init_data(&factory, p_cur_file_abs_path);
        do_work(p_cur_file_abs_path, &factory);

        char out_file_abs_path_buf[1024]={0};
        if (factory.mode == ENCRYPT_MODE) {
            strcpy(out_file_abs_path_buf, stParam.out);
            path_join_mp(out_file_abs_path_buf, (char*)get_basename(p_cur_file_abs_path));
            strcat(out_file_abs_path_buf, ".03");
            save_file(out_file_abs_path_buf, factory.encrypted, factory.encrypted_used_size);
        } else if (factory.mode == DECRYPT_MODE) {
            strcpy(out_file_abs_path_buf, stParam.out);
            path_join_mp(out_file_abs_path_buf, (char*)get_basename(p_cur_file_abs_path));
            remove_last_suffix(out_file_abs_path_buf, ".03");
            save_file(out_file_abs_path_buf, factory.decrypted, factory.decrypted_used_size);
        }

        printlnLog("[finish] save as %s\n", out_file_abs_path_buf);
        //next
        p_cur_file_abs_path = p_cur_file_abs_path + strlen(p_cur_file_abs_path)+1;
    }

    clean_factory(&factory);
NOT_EXIT:
    if (stParam.isExit == 1) {
        sleep(999999);
        goto NOT_EXIT;
    }
EXIT:
    return 0;
}

