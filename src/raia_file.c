#include "raia_file.h"

#include <stdio.h>

#ifdef __WINDOWS__
#define RAIA_EXPORT __declspec(dllexport) 
#else
#define RAIA_EXPORT
#endif

RAIA_EXPORT void *raia_file_exist(const char *s, void *p, int n) {
    const char *path = json_get_string(s, "path");
    int exist = file_check_path(path); // 0 = 存在しない, 1 = ファイルがある, 2 = パスがある
    const char *ret = json_add_number(NULL, "result", exist);
    free((void *)path);
    return (void *)ret;
}

RAIA_EXPORT void *raia_file_load_string(const char *s, void *p, int n) {
    const char *path = json_get_string(s, "path");
    const char *str = file_load_string(path);
    const char *ret = json_add_string(NULL, "result", str);
    free((void *)path);
    free((void *)str);
    return (void *)ret;
}

RAIA_EXPORT void *raia_file_save_string(const char *s, void *p, int n) {
    const char *path = json_get_string(s, "path");
    const char *str = json_get_string(s, "data");
    file_save_string(path, str);
    const char *ret = json_add_boolean(NULL, "result", 1);
    free((void *)path);
    free((void *)str);
    return (void *)ret;
}

RAIA_EXPORT void *raia_file_load_binary(const char *s, void *p, int n) {
    const char *filename = json_get_string(s, "path");

    size_t file_size;
    uint8_t *file_data = file_load_binary(filename, &file_size);
    if (file_data == NULL) {
        fprintf(__stderrp, "Failed to read binary file: %s", filename);
        return NULL;
    }
    free((void *)filename);
    return file_data;
}

RAIA_EXPORT void *raia_file_save_binary(const char *s, void *p, int n) {
    const char *filename = json_get_string(s, "path");
    size_t data_size = n;
    uint8_t *data = p;
    int result = file_save_binary(filename, data, data_size);
    const char *ret;
    if (result == 0) {
        ret = json_add_boolean(NULL, "result", 1);
    } else {
        ret = json_add_boolean(NULL, "result", 0);
    }
    free((void *)filename);
    return (void *)ret;
}

RAIA_EXPORT void *raia_file_get_exe_path(const char *s, void *p, int n) {
    char *path = get_exe_path();
    const char *ret = json_add_string(NULL, "result", path);
    return (void *)ret;
}

RAIA_EXPORT void *raia_file_get_cur_path(const char *s, void *p, int n) {
    char *path = get_current_path();
    const char *ret = json_add_string(NULL, "result", path);
    return (void *)ret;
}

RAIA_EXPORT void *raia_file_get_dirs(const char *s, void *p, int n) {
    const char *path = json_get_string(s, "path");
    char **directories = NULL;
    size_t count = 0;
    get_directories(path, &directories, &count);

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    JSON_Value *directories_value = json_value_init_array();
    JSON_Array *directories_array = json_value_get_array(directories_value);

    for (int i = 0; i < count; i++) {
        json_array_append_string(directories_array, directories[i]);
    }

    json_object_set_value(root_object, "result", directories_value);
    char *serialized_string = json_serialize_to_string(root_value);

    json_value_free(root_value);
    free((void *)path);
    return serialized_string;
}

RAIA_EXPORT void *raia_file_get_dirs_all(const char *s, void *p, int n) {
    const char *path = json_get_string(s, "path");
    char **directories = NULL;
    size_t count = 0;
    get_directories_recursive(path, &directories, &count);
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    JSON_Value *directories_value = json_value_init_array();
    JSON_Array *directories_array = json_value_get_array(directories_value);

    for (int i = 0; i < count; i++) {
        json_array_append_string(directories_array, directories[i]);
    }

    json_object_set_value(root_object, "result", directories_value);
    char *serialized_string = json_serialize_to_string(root_value);

    json_value_free(root_value);
    free((void *)path);
    return serialized_string;
}

//RAIA_EXPORT void *raia_file_get_dirs_all(const char *s, void *p, int n) {
//    const char *path = json_get_string(s, "path");
//    char **directories = NULL;
//    size_t count = 0;
//    get_directories_recursive(path, &directories, &count);
//    duk_idx_t arr_idx = duk_push_array(ctx);
//    for (size_t i = 0; i < count; i++) {
//        duk_push_string(ctx, directories[i]);
//        duk_put_prop_index(ctx, arr_idx, i);
//    }
//    return 1;
//}
//
//RAIA_EXPORT void *raia_file_get_dirs(const char *s, void *p, int n) {
//    const char *path = duk_to_string(ctx, 0);
//    char **directories = NULL;
//    size_t count = 0;
//    get_directories(path, &directories, &count);
//    duk_idx_t arr_idx = duk_push_array(ctx);
//    for (size_t i = 0; i < count; i++) {
//        duk_push_string(ctx, directories[i]);
//        duk_put_prop_index(ctx, arr_idx, i);
//    }
//    return 1;
//}

//RAIA_EXPORT duk_ret_t raia_file_exist(duk_context *ctx) {
//    const uint8_t *path = (uint8_t *) duk_to_string(ctx, 0);
//    int exist = file_check_path(path); // 0 = 存在しない, 1 = ファイルがある, 2 = パスがある
//    duk_push_int(ctx, exist);
//    return 1;
//}

//RAIA_EXPORT duk_ret_t raia_file_load_string(duk_context *ctx) {
//    const uint8_t *path = (uint8_t *) duk_to_string(ctx, 0);
//    const uint8_t *str = file_load_string(path);
//    duk_push_string(ctx, str);
//    free(str);
//    return 1;
//}

//RAIA_EXPORT duk_ret_t raia_file_save_string(duk_context *ctx) {
//    const uint8_t *path = (uint8_t *) duk_to_string(ctx, 0);
//    const uint8_t *str = (uint8_t *) duk_to_string(ctx, 1);
//    file_save_string(path, str);
//    duk_push_string(ctx, str);
//    return 1;
//}

//// JSONファイルを読み込んでJSONオブジェクトに変換し、Duktapeに渡す関数
//RAIA_EXPORT duk_ret_t raia_file_load_json(duk_context *ctx) {
//    const char *filename = duk_require_string(ctx, 0);
//    char *json_string = file_load_string(filename);
//
//    if (json_string == NULL) {
//        duk_error(ctx, DUK_ERR_TYPE_ERROR, "Failed to load JSON file: %s", filename);
//        return 0;  // Unreachable, but keeps compiler happy
//    }
//
//    duk_push_string(ctx, json_string);
//    duk_json_decode(ctx, -1);
//
//    free(json_string);  // Don't forget to free the allocated memory
//
//    return 1;  // JSON object is on the stack
//}
//
//// Duktapeから渡されたJSONオブジェクトを読み込んで文字列に変換し、ファイルに書き込む関数
//RAIA_EXPORT duk_ret_t raia_file_save_json(duk_context *ctx) {
//    const char *filename = duk_require_string(ctx, 0);
//
//    duk_require_object_coercible(ctx, 1);
//    duk_json_encode(ctx, 1);
//    const char *json_string = duk_get_string(ctx, -1);
//
//    file_save_string(filename, json_string);
//
//    return 0;  // No value returned
//}

//RAIA_EXPORT duk_ret_t raia_file_load_binary(duk_context *ctx) {
//    const char *filename = duk_require_string(ctx, 0);
//
//    size_t file_size;
//    uint8_t *file_data = file_load_binary(filename, &file_size);
//    if (file_data == NULL) {
//        duk_error(ctx, DUK_ERR_ERROR, "Failed to read binary file: %s", filename);
//        return 0;
//    }
//
//    void *buf = duk_push_buffer(ctx, file_size, 0);
//    memcpy(buf, file_data, file_size);
//    free(file_data);
//
//    return 1;
//}
//
//RAIA_EXPORT duk_ret_t raia_file_save_binary(duk_context *ctx) {
//    const char *filename = duk_require_string(ctx, 0);
//    duk_size_t data_size;
//    uint8_t *data = (uint8_t *) duk_require_buffer_data(ctx, 1, &data_size);
//
//    int result = file_save_binary(filename, data, data_size);
//
//    if (result == 0) {
//        duk_push_true(ctx);
//    } else {
//        duk_push_false(ctx);
//    }
//
//    return 1;
//}

//RAIA_EXPORT duk_ret_t raia_file_get_exe_path(duk_context *ctx) {
//    char *ret = get_exe_path();
//    duk_push_string(ctx, ret);
//    return 1;
//}
//
//RAIA_EXPORT duk_ret_t raia_file_get_cur_path(duk_context *ctx) {
//    char *ret = get_current_path();
//    duk_push_string(ctx, ret);
//    return 1;
//}
//
//RAIA_EXPORT duk_ret_t raia_file_get_dirs_all(duk_context *ctx) {
//    const char *path = duk_to_string(ctx, 0);
//    char **directories = NULL;
//    size_t count = 0;
//    get_directories_recursive(path, &directories, &count);
//    duk_idx_t arr_idx = duk_push_array(ctx);
//    for (size_t i = 0; i < count; i++) {
//        duk_push_string(ctx, directories[i]);
//        duk_put_prop_index(ctx, arr_idx, i);
//    }
//    return 1;
//}
//
//RAIA_EXPORT duk_ret_t raia_file_get_dirs(duk_context *ctx) {
//    const char *path = duk_to_string(ctx, 0);
//    char **directories = NULL;
//    size_t count = 0;
//    get_directories(path, &directories, &count);
//    duk_idx_t arr_idx = duk_push_array(ctx);
//    for (size_t i = 0; i < count; i++) {
//        duk_push_string(ctx, directories[i]);
//        duk_put_prop_index(ctx, arr_idx, i);
//    }
//    return 1;
//}