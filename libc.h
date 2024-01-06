#ifndef __LIBC_H
#define __LIBC_H

#include <stdint.h>
#include <stddef.h>

#include "gemdos.h"

#define MALLOC_MIN_ALLOCATION 32

#ifndef __cplusplus
#define NULL ((void *)0)
#endif

extern FILE *stdout;
extern void _exit(uint16_t retval);

struct memblock_t {
    struct memblock_t *next;
    struct memblock_t *prev;
    size_t size;
    uint8_t used;
};

int printf(const char *format, ...);
int sprintf(char *dest, const char *format, ...);
void putchar(char c);
int puts(const char *s);
size_t strlen(const char *s);
void exit(uint16_t retval);
int16_t isdigit(char c);
void memcpy(void *dest, const void *src, size_t bytes);
void strcpy(char *dest, const char *src);
int memcmp(const void *s1, const void *s2, size_t n);
void *memset(void *dest, int c, size_t bytes);

void malloc_init(size_t memsize);

void abort();

/* For dlmalloc */
#define O_RDWR 0
#define ENOMEM 0
#define EINVAL 0
#define PROT_READ 0
#define PROT_WRITE 0
#define MAP_ANONYMOUS 0
#define MAP_PRIVATE 0

/* Provided by dlmalloc */
void *malloc(size_t size);
void free(void *m);

#endif
