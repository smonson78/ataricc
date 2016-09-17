#include "aes_window.h"
#include "aes.h"

int16_t wind_create(int16_t wi_crkind, int16_t wi_crwx,
  int16_t wi_crwy, int16_t wi_crww, int16_t wi_crwh)
{
  int_in[0] = wi_crkind;
  int_in[1] = wi_crwx;
  int_in[2] = wi_crwy;
  int_in[3] = wi_crww;
  int_in[4] = wi_crwh;

  return crys_if(100);
}

int16_t wind_open(int16_t wi_ohandle, int16_t wi_owx,
  int16_t wi_owy, int16_t wi_oww, int16_t wi_owh)
{
  int_in[0] = wi_ohandle;
  int_in[1] = wi_owx;
  int_in[2] = wi_owy;
  int_in[3] = wi_oww;
  int_in[4] = wi_owh;

  return crys_if(101);
}

