//
// Created by dolphilia on 2023/05/08.
//

#include "wrapper_parson.h"

#define JSON_PARSE_STRING_GET_OBJECT(value, string, object)         \
do {                                                                \
    value = json_parse_string(string);                              \
    if (value == NULL) {                                            \
        fprintf(stderr, "Error: Unable to parse JSON string.\n");   \
        return NULL;                                                \
    }                                                               \
    object = json_value_get_object(value);                          \
} while(0)

char *json_get_string(const char *json_str, const char *key) {
    JSON_Value *root_value;
    JSON_Object *root_object;
    const char *value;
    root_value = json_parse_string(json_str);
    if (root_value == ((void *) 0)) {
        fprintf(__stderrp, "Error: Unable to parse JSON string.\n");
        return ((void *) 0);
    }
    root_object = json_value_get_object(root_value);
    value = json_object_get_string(root_object, key);
    char *result = (char *)malloc(sizeof(char*) * strlen(value));
    strcpy(result, value);
    json_object_clear(root_object);
    json_value_free(root_value);
    return result;
}

double json_get_number(const char *json_str, const char *key) {
    JSON_Value *root_value;
    JSON_Object *root_object;
    double result;
    root_value = json_parse_string(json_str);
    if (root_value == ((void *) 0)) {
        fprintf(__stderrp, "Error: Unable to parse JSON string.\n");
        return 0;
    }
    root_object = json_value_get_object(root_value);
    result = json_object_get_number(root_object, key);
    json_object_clear(root_object);
    json_value_free(root_value);
    return result;
}

int json_get_boolean(const char *json_str, const char *key) {
    JSON_Value *root_value;
    JSON_Object *root_object;
    int result;
    root_value = json_parse_string(json_str);
    if (root_value == ((void *) 0)) {
        fprintf(__stderrp, "Error: Unable to parse JSON string.\n");
        return 0;
    }
    root_object = json_value_get_object(root_value);
    result = json_object_get_boolean(root_object, key);
    json_object_clear(root_object);
    json_value_free(root_value);
    return result;
}

char *json_add_number(const char *json_str, const char *key, double value) {
    if (json_str == NULL || strlen(json_str) == 0) {
        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_number(root_object, key, value);
        char *serialized_json = json_serialize_to_string_pretty(root_value);
        json_value_free(root_value);
        return serialized_json;
    } else {
        JSON_Value *root_value = json_parse_string(json_str);
        if (root_value == ((void *) 0)) {
            fprintf(__stderrp, "Error: Unable to parse JSON string.\n");
            return ((void *) 0);
        }
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_number(root_object, key, value);
        char *serialized_json = json_serialize_to_string_pretty(root_value);
        json_value_free(root_value);
        free((void *)json_str);
        return serialized_json;
    }
}

char *json_add_string(const char *json_str, const char *key, const char *value) {
    if (json_str == NULL || strlen(json_str) == 0) {
        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_string(root_object, key, value);
        char *serialized_json = json_serialize_to_string_pretty(root_value);
        json_value_free(root_value);
        return serialized_json;
    } else {
        JSON_Value *root_value = json_parse_string(json_str);
        if (root_value == ((void *) 0)) {
            fprintf(__stderrp, "Error: Unable to parse JSON string.\n");
            return ((void *) 0);
        }
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_string(root_object, key, value);
        char *serialized_json = json_serialize_to_string_pretty(root_value);
        json_value_free(root_value);
        free((void *)json_str);
        return serialized_json;
    }
}

char *json_add_boolean(const char *json_str, const char *key, int value) {
    if (json_str == NULL || strlen(json_str) == 0) {
        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_boolean(root_object, key, value);
        char *serialized_json = json_serialize_to_string_pretty(root_value);
        json_value_free(root_value);
        return serialized_json;
    } else {
        JSON_Value *root_value = json_parse_string(json_str);
        if (root_value == ((void *) 0)) {
            fprintf(__stderrp, "Error: Unable to parse JSON string.\n");
            return ((void *) 0);
        }
        JSON_Object *root_object = json_value_get_object(root_value);
        json_object_set_boolean(root_object, key, value);
        char *serialized_json = json_serialize_to_string_pretty(root_value);
        json_value_free(root_value);
        free((void *)json_str);
        return serialized_json;
    }
}