#ifndef __TOS_H
#define __TOS_H

#include <stdint.h>

// TOS
int32_t Cconin();
void Cconws(const char* s);
void Cconout(const uint16_t ch);
int32_t Cnecin();

void *Malloc(int32_t number);
int32_t Mfree(void *block);
int32_t Mshrink(void *block, int32_t newsize);

// XBIOS
int32_t Random();
int16_t Getrez();

#endif
