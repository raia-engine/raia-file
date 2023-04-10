#ifndef RAIA_FILE_RAIA_FILE_H
#define RAIA_FILE_RAIA_FILE_H

#include "duktape/duktape.h"
#include "util/util_path.h"
#include "util/util_file.h"

#ifdef __WINDOWS__
#define RAIA_EXPORT __declspec(dllexport) 
#else
#define RAIA_EXPORT
#endif

RAIA_EXPORT duk_ret_t raia_file_exist(duk_context *ctx);
RAIA_EXPORT duk_ret_t raia_file_load_string(duk_context *ctx);
RAIA_EXPORT duk_ret_t raia_file_save_string(duk_context *ctx);
RAIA_EXPORT duk_ret_t raia_file_load_json(duk_context *ctx);
RAIA_EXPORT duk_ret_t raia_file_save_json(duk_context *ctx);
RAIA_EXPORT duk_ret_t raia_file_load_binary(duk_context *ctx);
RAIA_EXPORT duk_ret_t raia_file_save_binary(duk_context *ctx);

#endif //RAIA_FILE_RAIA_FILE_H
