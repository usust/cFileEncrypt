//
// Created by lyu on 6/26/24.
//

#include "fileio.h"
#include "../share.h"
#include "win.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int getFileAbsPathListMP(const char* p_dir, char* io_buf, const int buf_size) {
#ifdef  RUN_WINDOWS_OS
    printlnLog("[+] windows run getFile    \n");
    return getFilePathWindows(p_dir, io_buf, buf_size);
#else
    return 0;
#endif
}

int read_file(const char* filename, char* buffer) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printlnLog("[!] read file error\n");
    }

    int old_offset = (int)ftell(file);
    fseek(file, 0, SEEK_END);
    int file_size = (int)ftell(file);
    fseek(file, old_offset, SEEK_SET);

    fread(buffer, 1, file_size, file);
    fclose(file);

    return file_size;
}

int save_file(const char* filename, const char* buffer, int size) {
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fwrite(buffer, 1, size, file);

    // 关闭文件
    fclose(file);

    return 0;
}

const char* get_basename(const char* path) {
    if (path == NULL) {
        return NULL;
    }

    const char* slash = strrchr(path, '/');
    const char* backslash = strrchr(path, '\\');

    // 取最后一个分隔符的位置
    const char* last_sep = slash > backslash ? slash : backslash;

    // 如果没有分隔符，直接返回原路径
    if (last_sep == NULL) {
        return path;
    }

    // 返回分隔符后的文件名
    return last_sep + 1;
}

void path_join_mp(char* path_buf, char* filename) {
#ifdef  RUN_WINDOWS_OS
    int i = 0;
    for (; i < strlen(path_buf); i++) {
        if (path_buf[i] == '/') {
            path_buf[i] = '\\';
        }
    }
    path_buf[i] = 0;
    strcat(path_buf, "\\");
    strcat(path_buf, filename);
#endif
}