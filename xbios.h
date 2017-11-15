#ifndef __XBIOS_H
#define __XBIOX_H

#include <libc.h>
#include <stdint.h>

int32_t xbios_supexec(int32_t (*func)());

#endif
