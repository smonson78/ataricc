#ifndef __LIBC_H
#define __LIBC_H

#include <stdint.h>

typedef uint16_t FILE;
typedef uint32_t size_t;
#define NULL ((void *)0)

extern FILE *stdout;
extern void _exit(uint16_t retval);

int printf(const char *format, ...);
int puts(const char *s);
void memcpy(void *dest, void *src, size_t bytes);
void exit(uint16_t retval);
int16_t isdigit(char c);

#endif
