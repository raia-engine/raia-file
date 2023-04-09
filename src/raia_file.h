#ifndef RAIA_FILE_RAIA_FILE_H
#define RAIA_FILE_RAIA_FILE_H

#ifdef __WINDOWS__
#define RAIA_EXPORT __declspec(dllexport) 
#else
#define RAIA_EXPORT
#endif

void hello(void);

#endif //RAIA_FILE_RAIA_FILE_H
