#include "raia_file.h"

#include <stdio.h>

#ifdef __WINDOWS__
#define RAIA_EXPORT __declspec(dllexport) 
#else
#define RAIA_EXPORT
#endif

void hello(void) {
    printf("Hello, World!\n");
}
