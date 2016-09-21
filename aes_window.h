#ifndef __AES_WINDOW_H
#define __AES_WINDOW_H

#include <stdint.h>

typedef enum {
    WF_KIND = 1,
    WF_NAME,
    WF_INFO,
    WF_WORKXYWH,
    WF_CURRXYWH,
    WF_PREVXYWH,
    WF_FULLXYWH,
    WF_HSLIDE,
    WF_VSLIDE,
    WF_TOP,
    WF_FIRSTXYWH,
    WF_NEXTXYWH,
    WF_IGNORE,
    WF_VSLSIZE = 16
} WF_Function;


int16_t wind_create(int16_t wi_crkind, int16_t wi_crwx,
  int16_t wi_crwy, int16_t wi_crww, int16_t wi_crwh);

int16_t wind_open(int16_t wi_ohandle, int16_t wi_owx,
  int16_t wi_owy, int16_t wi_oww, int16_t wi_owh);
  
int16_t wind_set(int16_t wi_shandle, WF_Function wi_sfield,
    int16_t wi_sw1, int16_t wi_sw2, int16_t wi_sw3, int16_t wi_sw4);

int16_t wind_get(int16_t wi_ghandle, WF_Function wi_gfield,
    int16_t *wi_gw1, int16_t *wi_gw2, int16_t *wi_gw3, int16_t *wi_gw4);

int16_t wind_update(int16_t wi_ubegend);

int16_t wind_calc(int16_t wi_ctype, int16_t wi_ckind,
    int16_t wi_cinx, int16_t wi_ciny,
    int16_t wi_cinw, int16_t wi_cinh,
    int16_t *coutx, int16_t *couty,
    int16_t *coutw, int16_t *couth);


#endif
