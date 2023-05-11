//
// Created by dolphilia on 2023/05/08.
//

#ifndef RAIA_FILE_WRAPPER_PARSON_H
#define RAIA_FILE_WRAPPER_PARSON_H

#include "../parson/parson.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double json_get_number(const char *json_str, const char *key);
char *json_get_string(const char *json_str, const char *key);
int json_get_boolean(const char *json_str, const char *key);
char *json_add_number(const char *json_str, const char *key, double value);
char *json_add_string(const char *json_str, const char *key, const char *value);
char *json_add_boolean(const char *json_str, const char *key, int value);

#endif //RAIA_FILE_WRAPPER_PARSON_H
