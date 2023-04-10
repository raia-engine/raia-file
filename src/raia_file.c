#include "raia_file.h"

#include <stdio.h>

#ifdef __WINDOWS__
#define RAIA_EXPORT __declspec(dllexport) 
#else
#define RAIA_EXPORT
#endif

RAIA_EXPORT duk_ret_t raia_file_exist(duk_context *ctx) {
    const uint8_t* path = (uint8_t *)duk_to_string(ctx, 0);
    int exist = check_path(path); // 0 = 存在しない, 1 = ファイルがある, 2 = パスがある
    duk_push_int(ctx, exist);
    return 1;
}

RAIA_EXPORT duk_ret_t raia_file_load_string(duk_context *ctx) {
    const uint8_t* path = (uint8_t *)duk_to_string(ctx, 0);
    const uint8_t* str = load_string(path);
    duk_push_string(ctx, str);
    free(str);
    return 1;
}

RAIA_EXPORT duk_ret_t raia_file_save_string(duk_context *ctx) {
    const uint8_t* path = (uint8_t *)duk_to_string(ctx, 0);
    const uint8_t* str = (uint8_t *)duk_to_string(ctx, 1);
    save_string(path, str);
    duk_push_string(ctx, str);
    return 1;
}

// JSONファイルを読み込んでJSONオブジェクトに変換し、Duktapeに渡す関数
RAIA_EXPORT duk_ret_t raia_file_load_json(duk_context *ctx) {
    const char *filename = duk_require_string(ctx, 0);
    char *json_string = load_string(filename);

    if (json_string == NULL) {
        duk_error(ctx, DUK_ERR_TYPE_ERROR, "Failed to load JSON file: %s", filename);
        return 0;  // Unreachable, but keeps compiler happy
    }

    duk_push_string(ctx, json_string);
    duk_json_decode(ctx, -1);

    free(json_string);  // Don't forget to free the allocated memory

    return 1;  // JSON object is on the stack
}

// Duktapeから渡されたJSONオブジェクトを読み込んで文字列に変換し、ファイルに書き込む関数
RAIA_EXPORT duk_ret_t raia_file_save_json(duk_context *ctx) {
    const char *filename = duk_require_string(ctx, 0);

    duk_require_object_coercible(ctx, 1);
    duk_json_encode(ctx, 1);
    const char *json_string = duk_get_string(ctx, -1);

    save_string(filename, json_string);

    return 0;  // No value returned
}

RAIA_EXPORT duk_ret_t raia_file_load_binary(duk_context *ctx) {
    const char *filename = duk_require_string(ctx, 0);

    size_t file_size;
    uint8_t *file_data = load_binary(filename, &file_size);
    if (file_data == NULL) {
        duk_error(ctx, DUK_ERR_ERROR, "Failed to read binary file: %s", filename);
        return 0;
    }

    void *buf = duk_push_buffer(ctx, file_size, 0);
    memcpy(buf, file_data, file_size);
    free(file_data);

    return 1;
}

RAIA_EXPORT duk_ret_t raia_file_save_binary(duk_context *ctx) {
    const char *filename = duk_require_string(ctx, 0);
    duk_size_t data_size;
    uint8_t *data = (uint8_t *) duk_require_buffer_data(ctx, 1, &data_size);

    int result = save_binary(filename, data, data_size);

    if (result == 0) {
        duk_push_true(ctx);
    } else {
        duk_push_false(ctx);
    }

    return 1;
}
