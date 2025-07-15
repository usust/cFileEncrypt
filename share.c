#include "share.h"

#include <stdarg.h>
#include <stdio.h>
//
// Created by lyu on 6/26/24.
//

void printlnLog(const char* format, ...) {
#ifdef RUN_LOG
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}