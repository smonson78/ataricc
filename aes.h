#ifndef __AES_H
#define __AES_H

#include <stdint.h>

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

#endif
