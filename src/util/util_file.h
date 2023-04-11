//
// Created by dolphilia on 2023/04/10.
//

#ifndef RAIA_FILE_UTIL_FILE_H
#define RAIA_FILE_UTIL_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../platform.h"

char *load_string(const char *filename);
int save_string(const char *filename, const char *content);
uint8_t *load_binary(const char *filename, size_t *file_size);
int save_binary(const char *filename, uint8_t *data, size_t data_size);

#endif //RAIA_FILE_UTIL_FILE_H
