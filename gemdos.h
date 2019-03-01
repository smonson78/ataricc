#ifndef GEMDOS_H_
#define GEMDOS_H_

#include "tos.h"
#include "aes.h"

typedef uint16_t FILE;

// FIXME: these should be O_... but dlmalloc has used them!
#define GEMDOS_RDONLY 1
#define GEMDOS_WRONLY 2
#define GEMDOS_RDWR 4


int32_t gemdos_super(void *stack);

/* File IO */
int16_t Fcreate(const int8_t *fname, int16_t attr);
int32_t Fopen(const char *fname, int16_t mode);
void Fclose(FILE handle);

int32_t Fwrite(FILE handle, int32_t count, void *buf);
int32_t Fread(FILE handle, int32_t count, void *buf);

#endif
