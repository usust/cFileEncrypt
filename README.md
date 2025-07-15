# 文件加密程序

```sh
Usage: <run mode> <file path...>
-E --encrypt: encrypt files
-D --decrypt: decrypt files
-I --input input directory
    * means all files in current directory.
-O --out: out directory
-R --running: not exit the process
Example 1: FileEncrypt -E *
    encrypt all files not incloud FileEncrypt execuate program file in the current directory.
Example 2: FileEncrypt -E -I ./in -O ./out
    encrypt all files in the in directory and output files into out directory.
```

## 编译

```sh
cmake -S . -B build
cd build
make
```

### macOS build exe

``` sh

makedir build-win
cd build-win
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw64.cmake
make
```


## 加解密功能配置

程序默认都允许加密，解密功能受 `RUN_DECRYPT` 宏控制。如果定义了此宏，则具备解密功能。`RUN_DECRYPT` 宏在**CMakeLists.txt**中配置。


# 忽略任何目录下的包含 "build" 字符串的文件夹
*/build*/*

# 其他忽略规则
# ...