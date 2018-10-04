#ifndef __LIBC_H
#define __LIBC_H

#include <stdint.h>

#define MALLOC_MIN_ALLOCATION 32

typedef uint16_t FILE;
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
size_t strlen(const char *s);
void exit(uint16_t retval);
int16_t isdigit(char c);

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
