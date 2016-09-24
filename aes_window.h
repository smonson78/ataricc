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

typedef enum {
    END_UPDATE = 0,
    BEG_UPDATE = 1
} WU_Type;

typedef enum {
    WC_BORDER,
    WC_WORK
} WC_Type;

#define WIND_NAME (1<<0)
#define WIND_CLOSER (1<<1)
#define WIND_FULLER (1<<2)
#define WIND_MOVER (1<<3)
#define WIND_INFO (1<<4)
#define WIND_SIZER (1<<5)
#define WIND_UPARROW (1<<6)
#define WIND_DNARROW (1<<7)
#define WIND_VSLIDE (1<<8)
#define WIND_LFARROW (1<<9)
#define WIND_RTARROW (1<<10)
#define WIND_HSLIDE (1<<11)
#define WIND_BASIC (WIND_NAME|WIND_MOVER|WIND_CLOSER|WIND_FULLER|WIND_SIZER)

int16_t wind_create(int16_t wi_crkind, int16_t wi_crwx,
  int16_t wi_crwy, int16_t wi_crww, int16_t wi_crwh);

int16_t wind_open(int16_t wi_ohandle, int16_t wi_owx,
  int16_t wi_owy, int16_t wi_oww, int16_t wi_owh);
  
int16_t wind_set(int16_t wi_shandle, WF_Function wi_sfield,
    int16_t wi_sw1, int16_t wi_sw2, int16_t wi_sw3, int16_t wi_sw4);

int16_t wind_get(int16_t wi_ghandle, WF_Function wi_gfield,
    int16_t *wi_gw1, int16_t *wi_gw2, int16_t *wi_gw3, int16_t *wi_gw4);

int16_t wind_update(WU_Type wi_ubegend);

int16_t wind_calc(WC_Type wi_ctype, int16_t wi_ckind,
    int16_t wi_cinx, int16_t wi_ciny,
    int16_t wi_cinw, int16_t wi_cinh,
    int16_t *coutx, int16_t *couty,
    int16_t *coutw, int16_t *couth);

int16_t wind_close(int16_t wi_clhandle);
int16_t wind_delete(int16_t wi_dhandle);


#endif
