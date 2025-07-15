//
// Created by lyu on 6/26/24.
//

#ifndef FILEIO_H
#define FILEIO_H

/**
 * get the list of files in a directory. the format like:
 * string1\0string2\0....
 * support multi-platform (Windows, macOS)
 *
 * @param p_dir search directory
 * @param io_buf: the address of the buffer
 * @param buf_size: the size of the buffer
 * @return the number of files
 */
int getFileAbsPathListMP(const char* p_dir, char* io_buf, int buf_size);

int read_file(const char* filename, char* buffer);

int save_file(const char* filename, const char* buffer, int size);

const char* get_basename(const char* path);

/**
 * 
 * @param path
 */
void format_path(char *path);

/**
 * 
 * @param path_buf the buffer of save
 * @param filename base file name
 */
void path_join_mp(char* path_buf, char* filename);
#endif //FILEIO_H
