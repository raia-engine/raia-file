//
// Created by dolphilia on 2023/04/10.
//

#include "util_file.h"

char *load_string(const char *filename) {
    size_t file_index = 0;
    char *str = NULL;
    FILE *file_ptr;

#ifdef __WINDOWS__
    fopen_s(&file_ptr, filename, "r");
#else
    file_ptr = fopen(filename, "r");
#endif

    if (file_ptr == NULL) {
        printf("Failed to load file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file_ptr, 0, SEEK_END);
    const size_t initial_size = ftell(file_ptr);
    size_t buffer_size = initial_size + 4;
    str = (char *) malloc(buffer_size + 1);
    fseek(file_ptr, 0, SEEK_SET);
    for (;;) {
        const int c = fgetc(file_ptr);
        if (c == EOF) {
            break;
        }
        const char ch = (char) c;
        if (buffer_size <= file_index) {
            buffer_size *= 2;
            str = (char *) realloc(str, buffer_size);
        }
        str[file_index] = ch;
        file_index++;
    }
    str[file_index] = '\0';
    fclose(file_ptr);
    return str;
}

int save_string(const char *filename, const char *content) {
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Write the content to the file
    if (fputs(content, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return 2;
    }

    // Close the file
    if (fclose(file) != 0) {
        perror("Error closing file");
        return 3;
    }

    return 0;
}

uint8_t *load_binary(const char *filename, size_t *file_size) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *buffer = (uint8_t *)malloc(size);
    if (buffer == NULL) {
        printf("Error allocating memory for file buffer.\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, size, file);
    if (bytes_read != size) {
        printf("Error reading file: %s\n", filename);
        fclose(file);
        free(buffer);
        return NULL;
    }

    fclose(file);

    if (file_size) {
        *file_size = size;
    }

    return buffer;
}

int save_binary(const char *filename, uint8_t *data, size_t data_size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    size_t written = fwrite(data, sizeof(uint8_t), data_size, file);
    fclose(file);

    if (written != data_size) {
        printf("Error: Unable to write all data to file %s\n", filename);
        return 1;
    }

    return 0;
}