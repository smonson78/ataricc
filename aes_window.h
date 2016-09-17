#ifndef __AES_WINDOW_H
#define __AES_WINDOW_H

#include <stdint.h>

int16_t wind_create(int16_t wi_crkind, int16_t wi_crwx,
  int16_t wi_crwy, int16_t wi_crww, int16_t wi_crwh);

int16_t wind_open(int16_t wi_ohandle, int16_t wi_owx,
  int16_t wi_owy, int16_t wi_oww, int16_t wi_owh);

#endif
