#ifndef __LIBC_H
#define __LIBC_H

#include <stdint.h>

#define MALLOC_MIN_ALLOCATION 32

typedef uint16_t FILE;
typedef uint32_t size_t;
#define NULL ((void *)0)

extern FILE *stdout;
extern void _exit(uint16_t retval);

struct memblock_t {
    struct memblock_t *next;
    struct memblock_t *prev;
    size_t size;
    uint8_t used;
};

extern struct memblock_t *malloc_head;
extern size_t malloc_total_size;

int printf(const char *format, ...);
int puts(const char *s);
void memcpy(void *dest, void *src, size_t bytes);
void memset(void *dest, int c, size_t bytes);
int memcmp(const void *s1, const void *s2, size_t n);
void exit(uint16_t retval);
int16_t isdigit(char c);

void malloc_init(size_t memsize);
void *malloc(size_t size);
void free(void *m);

#endif
