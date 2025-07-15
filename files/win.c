//
// Created by lyu on 25-7-14.
//

#include "win.h"
//
// Created by lyu on 25-7-14.
//

#include <windows.h>
#include <stdio.h>
#include <string.h>

// 辅助函数：将路径里的 '\' 替换成 '/'
void normalize_path(char* path) {
    for (int i = 0; path[i]; i++) {
        if (path[i] == '\\') {
            path[i] = '/';
        }
    }
}

int getFilePathWindows(const char* input, char file_name_buffer[], const int buffer_size) {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    char search_path[MAX_PATH];

    // 构造搜索路径: input + *
    if (input[strlen(input) - 1] == '\\' || input[strlen(input) - 1] == '/') {
        snprintf(search_path, MAX_PATH, "%s*", input);
    } else {
        snprintf(search_path, MAX_PATH, "%s\\*", input);
    }

    hFind = FindFirstFile(search_path, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("无法打开目录: %s\n", input);
        return -1;
    }

    int buffer_index = 0;
    int count = 0;

    do {
        if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
            char full_path[MAX_PATH];
            // 拼接完整路径，使用 Windows 原始的 '\'
            snprintf(full_path, MAX_PATH, "%s\\%s", input, findData.cFileName);

            // 转换路径为 '/'
            normalize_path(full_path);

            int path_len = strlen(full_path);
            if (buffer_index + path_len + 1 < buffer_size) {
                strcpy(&file_name_buffer[buffer_index], full_path);
                buffer_index += path_len + 1; // +1 for \0
                count++;
            } else {
                printf("Buffer不足，无法写入更多文件名。\n");
                break;
            }
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);

    // 末尾再补一个\0结束
    if (buffer_index < buffer_size) {
        file_name_buffer[buffer_index] = '\0';
    }

    return count;
}
