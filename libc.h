#ifndef __LIBC_H
#define __LIBC_H

#include <stdint.h>

typedef uint16_t FILE;

extern FILE *stdout;

int printf(const char *format, ...);
int puts(const char *s);


#endif
