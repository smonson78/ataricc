#include <aes.h>
#include <tos.h>
#include <libc.h>

static AESPB c;
static VDIPB v;

int16_t global[15];
int16_t control[12];
int16_t int_in[128];
int16_t int_out[128];
int16_t addr_in[128];
int16_t addr_out[128];

//int16_t global[15];
//int16_t control[5];
//int16_t int_in[16];
//int16_t int_out[7];
//int16_t addr_in[2];
//int16_t addr_out[1];

int16_t screen_phandle;
int16_t screen_vhandle;

int16_t screen_rez;
int16_t colour_screen;
int16_t x_max;
int16_t y_max;

uint8_t ctrl_cnts[][4] = {
	{10, 0, 1, 0 }, // appl_init
	{11, 2, 1, 1 }, // appl_read
	{12, 2, 1, 1 }, // appl_write
	{13, 0, 1, 1 }, // appl_find
	{14, 2, 1, 1 }, // appl_tplay
	{15, 1, 1, 1 }, // appl_trecord
	{16, 0, 0, 0 },
	{17, 0, 0, 0 },
	{18, 1, 3, 1 }, // appl_search (v4.0)
	{19, 0, 1, 0 }, // appl_exit
	{20, 0, 1, 0 }, // evnt_keybd
	{21, 3, 5, 0 }, // evnt_button
	{22, 5, 5, 0 }, // evnt_mouse
	{23, 0, 1, 1 }, // evnt_mesag
	{24, 2, 1, 0 }, // evnt_timer
	{25, 16, 7, 1}, // evnt_multi
	{26, 2, 1, 0 }, // evnt_dclick
	{27, 0, 0, 0 },
	{28, 0, 0, 0 },
	{29, 0, 0, 0 },
	{30, 1, 1, 1 }, // menu_bar
	{31, 2, 1, 1 }, // menu_icheck
	{32, 2, 1, 1 }, // menu_ienable
	{33, 2, 1, 1 }, // menu_tnormal
	{34, 1, 1, 2 }, // menu_text
	{35, 1, 1, 1 }, // menu_register
	{36, 2, 1, 2 }, // menu_popup (v3.3)
	{37, 2, 1, 2 }, // menu_attach (v3.3)
	{38, 3, 1, 1 }, // menu_istart (v3.3)
	{39, 1, 1, 1 }, // menu_settings (v3.3)
	{40, 2, 1, 1 }, // objc_add
	{41, 1, 1, 1 }, // objc_delete
	{42, 6, 1, 1 }, // objc_draw
	{43, 4, 1, 1 }, // objc_find
	{44, 1, 3, 1 }, // objc_offset
	{45, 2, 1, 1 }, // objc_order
	{46, 4, 2, 1 }, // objc_edit
	{47, 8, 1, 1 }, // objc_change
	{48, 4, 3, 0 }, // objc_sysvar (v3.4)
	{49, 0, 0, 0 },
	{50, 1, 1, 1 }, // form_do
	{51, 9, 1, 0 }, // form_dial
	{52, 1, 1, 1 }, // form_alert
	{53, 1, 1, 0 }, // form_error
	{54, 0, 5, 1 }, // form_center
	{55, 3, 3, 1 }, // form_keybd
	{56, 2, 2, 1 }, // form_button
	{57, 0, 0, 0 },
	{58, 0, 0, 0 },
	{59, 0, 0, 0 },
	{60, 0, 0, 0 },
	{61, 0, 0, 0 },
	{62, 0, 0, 0 },
	{63, 0, 0, 0 },
	{64, 0, 0, 0 },
	{65, 0, 0, 0 },
	{66, 0, 0, 0 },
	{67, 0, 0, 0 },
	{68, 0, 0, 0 },
	{69, 0, 0, 0 },
	{70, 4, 3, 0 }, // graf_rubberbox
	{71, 8, 3, 0 }, // graf_dragbox
	{72, 6, 1, 0 }, // graf_movebox
	{73, 8, 1, 0 }, // graf_growbox
	{74, 8, 1, 0 }, // graf_shrinkbox
	{75, 4, 1, 1 }, // graf_watchbox
	{76, 3, 1, 1 }, // graf_slidebox
	{77, 0, 5, 0 }, // graf_handle
	{78, 1, 1, 1 }, // graf_mouse
	{79, 0, 5, 0 }, // graf_mkstate
	{80, 0, 1, 1 }, // scrp_read
	{81, 0, 1, 1 }, // scrp_write
	{82, 0, 0, 0 },
	{83, 0, 0, 0 },
	{84, 0, 0, 0 },
	{85, 0, 0, 0 },
	{86, 0, 0, 0 },
	{87, 0, 0, 0 },
	{88, 0, 0, 0 },
	{89, 0, 0, 0 },
	{90, 0, 2, 2 }, // fsel_input
	{91, 0, 2, 3 }, // fsel_exinput
	{92, 0, 0, 0 },
	{93, 0, 0, 0 },
	{94, 0, 0, 0 },
	{95, 0, 0, 0 },
	{96, 0, 0, 0 },
	{97, 0, 0, 0 },
	{98, 0, 0, 0 },
	{99, 0, 0, 0 },
	{100, 5, 1, 0}, // wind_create
	{101, 5, 1, 0}, // wind_open
	{102, 1, 1, 0}, // wind_close
	{103, 1, 1, 0}, // wind_delete
	{104, 2, 5, 0}, // wind_get
	{105, 6, 1, 0}, // wind_set
	{106, 2, 1, 0}, // wind_find
	{107, 1, 1, 0}, // wind_update
	{108, 6, 5, 0}, // wind_calc
	{109, 0, 0, 0}, // wind_new
	{110, 0, 1, 1}, // rsrc_load
	{111, 0, 1, 0}, // rsrc_free
	{112, 2, 1, 0}, // rsrc_gaddr
	{113, 2, 1, 1}, // rsrc_saddr
	{114, 1, 1, 1}, // rsrc_obfix
	{115, 0, 0, 0}, // rsrc_rcfix (v4.0)
	{116, 0, 0, 0},
	{117, 0, 0, 0},
	{118, 0, 0, 0},
	{119, 0, 0, 0},
	{120, 0, 1, 2}, // shel_read
	{121, 3, 1, 2}, // shel_write
	{122, 1, 1, 1}, // shel_get
	{123, 1, 1, 1}, // shel_put
	{124, 0, 1, 1}, // shel_find
	{125, 0, 1, 2}, // shel_envrn
	{126, 0, 0, 0},
	{127, 0, 0, 0},
	{128, 0, 0, 0},
	{129, 0, 0, 0},
	{130, 1, 5, 0}, // appl_getinfo (v4.0)
};


void set_screen_attr()
{
	int16_t work_out[57];

	vq_extnd(screen_vhandle, 0, work_out); 
	x_max = work_out[0]; 
	y_max = work_out[1];
	screen_rez = Getrez(); /* 0 =  low,  1 = med,  2 = high */
	colour_screen = screen_rez < 2; /* mono 2,  colour 0 or 1 */
}


#if 1
// none of this is explained properly in tos.hyp

void aes()
{
    __asm__ __volatile__
    (
    	"move.l %0,%%d1\n\t"
		"move.w #200,%%d0\n\t"
		"trap #2\n\t"
    :
    : "p"(&c)
    : "d0", "d1"
    );
}


void vdi()
{
    __asm__ __volatile__
    (
        "move.l %0,%%d1\n\t"
        "move.w #115,%%d0\n\t"
        "trap #2\n\t"
    : /* outputs */
    : "p"(&v) /* inputs */
    : "d0", "d1" /* clobbered regs */
    );
}


int16_t appl_init()
{
	// Set up AESPB c
	c.cb_pcontrol = control;
	c.cb_pglobal = global;
	c.cb_pintin = int_in;
	c.cb_pintout = int_out;
	c.cb_padrin = addr_in;
	c.cb_padrout = addr_out;
	
	// Set up VDIPB
	v.contrl = control;
	v.intin = int_in;
	v.ptsin = addr_in;
	v.intout = int_out;
	v.ptsout = addr_out;

	control[4] = 0;
	global[0] = 0;
	global[2] = 0xffff;
	int_out[0] = 0xffff;
	crys_if(10);

	return int_out[0];
}

int16_t crys_if(int16_t opcode)
{
        int16_t i;

        control[0] = opcode;
        for (i = 1; i < 4; i++) {
	        control[i] = ctrl_cnts[opcode - 10][i];
        }
        
        printf("Calling AES with:\n");
        printf("\tc = 0x%p\n", c);
        printf("\tcontrol[0] = 0x%04x\n", c.cb_pcontrol[0]);
        printf("\tcontrol[1] = 0x%04x\n", c.cb_pcontrol[1]);
        printf("\tcontrol[2] = 0x%04x\n", c.cb_pcontrol[2]);
        printf("\tcontrol[3] = 0x%04x\n", c.cb_pcontrol[3]);
        printf("\tcontrol[4] = 0x%04x\n", c.cb_pcontrol[4]);
       
        aes();
        
        printf("\tResult = 0x%04x\n", int_out[0]);
        Cnecin();
        return int_out[0];
}

void vq_extnd (int16_t handle, int16_t owflag, int16_t *work_out)
{
	int_in[0] = owflag;

	control[0] = 102;
	control[1] = 0;
	control[3] = 1;
	control[6] = handle;

	vdi();

	memcpy(work_out, int_out, 45);
	memcpy(work_out + 45, addr_out, 12);
}

void v_opnvwk (int16_t *work_in, int16_t *handle, int16_t *work_out)
{
	//printf("v_opnwk()\n");
	memcpy(int_in, work_in, sizeof(int16_t) * 11);

	control[0] = 100;
	control[1] = 0;
	control[3] = 11;
	control[6] = *handle;

	//printf("about to call vdi()\n");
	//Cnecin();
	vdi();
	printf("Result: 0x%04x\n", int_out[0]);
	//Cnecin();
	
	*handle = control[6];
	memcpy(work_out, int_out, 45);
	memcpy(work_out + 45, addr_out, 12);
}

void v_clswk(int16_t handle)
{
   control[0] = 2;
   control[1] = 0;
   control[3] = 0;
   control[6] = handle;

   vdi();
}

void v_clsvwk(int16_t handle)
{
   control[0] = 101;
   control[1] = 0;
   control[3] = 0;
   control[6] = handle;

   vdi();
}

 	

int16_t graf_handle (int16_t *gr_hwchar, int16_t *gr_hhchar,
	int16_t *gr_hwbox, int16_t *gr_hhbox)
{
   crys_if(77);
   printf("* crys_if(77) called\n");
   Cnecin();

   *gr_hwchar = int_out[1];
   *gr_hhchar = int_out[2];
   *gr_hwbox  = int_out[3];
   *gr_hhbox  = int_out[4];

   return int_out[0];
}

int16_t appl_exit()
{
   return crys_if(19);
}





#endif
