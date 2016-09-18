#ifndef __AES_H
#define __AES_H

#include <stdint.h>

extern int16_t global[];
extern int16_t control[];
extern int16_t int_in[];
extern int16_t int_out[];
extern void *addr_in[];
extern void *addr_out[];

typedef struct
{
  int16_t *cb_pcontrol;  /* Pointer to control array */
  int16_t *cb_pglobal;   /* Pointer to global array  */
  int16_t *cb_pintin;    /* Pointer to int_in array  */
  int16_t *cb_pintout;   /* Pointer to int_out array */
  void **cb_padrin;    /* Pointer to adr_in array  */
  void **cb_padrout;   /* Pointer to adr_out array */
} AESPB;

typedef struct
{
	int16_t *contrl;    /* Pointer to control array */
	int16_t *intin;     /* Pointer to int_in array  */
	int16_t *ptsin;     /* Pointer to points in array  */
	int16_t *intout;    /* Pointer to int_out array */
	int16_t *ptsout;    /* Pointer to points out array */
} VDIPB;

// Mouse pointer form
typedef struct
{
  int16_t  mf_xhot;       /* X-position hot-spot */
  int16_t  mf_yhot;       /* Y-position hot-spot */
  int16_t  mf_nplanes;    /* Number of planes    */
  int16_t  mf_fg;         /* Mask colour         */
  int16_t  mf_bg;         /* Pointer colour      */
  int16_t  mf_mask[16];   /* Mask form           */
  int16_t  mf_data[16];   /* Pointer form        */
} MFORM;

void aes();
void vdi();
int16_t crys_if(int16_t opcode);

int16_t appl_init();
int16_t appl_exit();

void v_opnvwk (int16_t *work_in, int16_t *handle, int16_t *work_out);
void vq_extnd (int16_t handle, int16_t owflag, int16_t *work_out);

int16_t graf_mouse(int16_t gr_monumber, MFORM *gr_mofaddr);
int16_t graf_handle (int16_t *gr_hwchar, int16_t *gr_hhchar,
  int16_t *gr_hwbox, int16_t *gr_hhbox);

int16_t form_alert (int16_t fo_adefbttn, const char *fo_astring);

void v_clswk(int16_t handle);
void v_clsvwk(int16_t handle);
void set_screen_attr();

// event
int16_t evnt_mesag(int16_t *msg);
int16_t evnt_multi (int16_t ev_mflags,  int16_t ev_mbclicks,
    int16_t ev_mbmask,  int16_t ev_mbstate,
    int16_t ev_mm1flags, int16_t ev_mm1x,
    int16_t ev_mm1y, int16_t ev_mm1width,
    int16_t ev_mm1height, int16_t ev_mm2flags,
    int16_t ev_mm2x, int16_t ev_mm2y,
    int16_t ev_mm2width, int16_t ev_mm2height,
    int16_t *ev_mmgpbuff, int16_t ev_mtlocount,
    int16_t ev_mthicount, int16_t *ev_mmox,
    int16_t *ev_mmoy, int16_t *ev_mmbutton,
    int16_t *ev_mmokstate, int16_t *ev_mkreturn,
    int16_t *ev_mbreturn);
int16_t wind_set(int16_t wi_shandle, int16_t wi_sfield,
    int16_t wi_sw1, int16_t wi_sw2, int16_t wi_sw3, int16_t wi_sw4);

// vdi
int16_t vsf_color(int16_t handle, int16_t color_index);
void vr_recfl(int16_t handle, int16_t *pxyarray);
void v_bar(int16_t handle, int16_t *pxyarray);
int16_t vswr_mode(int16_t handle, int16_t mode);


int16_t wind_calc(int16_t wi_ctype, int16_t wi_ckind,
    int16_t wi_cinx, int16_t wi_ciny,
    int16_t wi_cinw, int16_t wi_cinh,
    int16_t *coutx, int16_t *couty,
    int16_t *coutw, int16_t *couth);
int16_t wind_get(int16_t wi_ghandle, int16_t wi_gfield,
    int16_t *wi_gw1, int16_t *wi_gw2, int16_t *wi_gw3, int16_t *wi_gw4);


#endif
