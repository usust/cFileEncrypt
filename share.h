//
// Created by lyu on 6/26/24.
//

#ifndef SHARE_H
#define SHARE_H

#define SUCCESS 0
#define _1MB_ 1024*1024
#define _100MB_ (_1MB_*100)

struct StCmdParams {
    int mode;
    const char* inputDir;
    char filenames[_1MB_];
    int fileCount;
    const char* out;
    // 执行完成后，是否直接退出程序
    // 0 -> 退出
    // 1 -> 不退出
    int isExit;
};


void printlnLog(const char* format, ...);
#endif //SHARE_H
