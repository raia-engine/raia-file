//
// Created by dolphilia on 2023/04/10.
//

#include "util_path.h"

int check_path(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == -1) {
        return 0; // パスが存在しない
    }
    if (S_ISREG(path_stat.st_mode)) {
        return 1; // パスがファイルを指している
    }
    if (S_ISDIR(path_stat.st_mode)) {
        return 2; // パスがディレクトリを指している
    }
    return 0; // その他の場合は存在しないものとして扱う
}