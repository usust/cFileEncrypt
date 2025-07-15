cmake_minimum_required(VERSION  3.22.1)

project(FileEnc C )
set(CMAKE_C_STANDARD 11)
#/toolchain-mingw64.cmake
#set(CMAKE_C_COMPILER "gcc")
#set(CMAKE_CXX_COMPILER "g++")
#add_definitions(-DMY_DEBUG)
# 输出运行信息
add_definitions(-DRUN_LOG)
add_definitions(-DRUN_DECRYPT)
add_definitions(-DRUN_WINDOWS_OS)
add_executable(FileEnc_d main.c
        files/fileio.c
        factory.c
        share.h
        share.c
        mycstring.c
        encrypt/exchange_byte.c
        encrypt/math_calc.c
        encrypt/xor.c
        files/win.c)
#是否优化
#set_target_properties(FileEncrypt PROPERTIES
#        LINK_FLAGS "-Wl,--strip-all"
#)