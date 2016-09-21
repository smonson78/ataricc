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

int16_t wind_get(int16_t wi_ghandle, WF_Function wi_gfield,
    int16_t *wi_gw1, int16_t *wi_gw2, int16_t *wi_gw3, int16_t *wi_gw4)
{
    int_in[0]  = wi_ghandle;
    int_in[1]  = (int16_t)wi_gfield;

    crys_if(104);

    *wi_gw1 = int_out[1];
    *wi_gw2 = int_out[2];
    *wi_gw3 = int_out[3];
    *wi_gw4 = int_out[4];

    return int_out[0];
}

int16_t wind_calc(int16_t wi_ctype, int16_t wi_ckind,
    int16_t wi_cinx, int16_t wi_ciny,
    int16_t wi_cinw, int16_t wi_cinh,
    int16_t *coutx, int16_t *couty,
    int16_t *coutw, int16_t *couth)
{
   int_in[0] = wi_ctype;
   int_in[1] = wi_ckind;
   int_in[2] = wi_cinx;
   int_in[3] = wi_ciny;
   int_in[4] = wi_cinw;
   int_in[5] = wi_cinh;

   crys_if(108);

   *coutx = int_out[1];
   *couty = int_out[2];
   *coutw = int_out[3];
   *couth = int_out[4];

   return int_out[0];
}

int16_t wind_set(int16_t wi_shandle, WF_Function wi_sfield,
    int16_t wi_sw1, int16_t wi_sw2, int16_t wi_sw3, int16_t wi_sw4)
{
   int_in[0] = wi_shandle;
   int_in[1] = wi_sfield;
   int_in[2] = wi_sw1;
   int_in[3] = wi_sw2;
   int_in[4] = wi_sw3;
   int_in[5] = wi_sw4;

   return crys_if(105);
}

int16_t wind_update(int16_t wi_ubegend)
{
    int_in[0] = wi_ubegend;
    return crys_if(107);
}


