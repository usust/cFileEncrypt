//
// Created by lyu on 6/27/24.
//

#include "mycstring.h"

#include <string.h>

void remove_last_suffix(char *path, const char *suffix) {
    const size_t len_path = strlen(path);
    const size_t len_suffix = strlen(suffix);

    // check length
    if (len_path < len_suffix) {
        return;
    }

    for (size_t i = len_path-len_suffix; i < len_path; i++) {
        if (path[i] != suffix[i - (len_path - len_suffix)]) {
            return; // 发现不匹配，直接返回
        }
    }

    path[len_path - len_suffix] = '\0';
}
