#include <tos.h>
#include <aes.h>
#include <aes_window.h>
#include <libc.h>

extern int16_t screen_phandle;
extern int16_t screen_vhandle;

int16_t window; // handle

int16_t open_vwork(int16_t phys_handle)
{
	int16_t work_in[11];
	int16_t work_out[57];
	int16_t new_handle;
	int16_t i;
	
	for (i = 0; i < 10; i++) {
		work_in[i] = 1;
	}
	work_in[10] = 2;
	new_handle = phys_handle;
	v_opnvwk(work_in, &new_handle, work_out);
	return new_handle;
}

void event_handler()
{
	int16_t quit = 0;
	int16_t msg[8];

    int16_t rect[4];
	while (!quit) {

        evnt_mesag(msg);
        
        switch (msg[0]) {
        case 22: // WM_CLOSED
            if (msg[3] == window)
                quit = 1;
            break;
        case 23: // WM_FULLED
            // get size of widow 0 (desktop)

            wind_get(0, 4, &rect[0], &rect[1], &rect[2], &rect[3]);

            wind_set(msg[3], 5/*WF_CURRXYWH*/,
                rect[0], rect[1], rect[2], rect[3]);
            break;
        case 28: // WM_MOVED
            wind_set(msg[3], 5/*WF_CURRXYWH*/,
                msg[4], msg[5], msg[6], msg[7]);
            break;
        case 27: // WM_SIZED
            wind_set(msg[3], 5/*WF_CURRXYWH*/,
                msg[4], msg[5], msg[6], msg[7]);
	            wind_get(window, 4, &rect[0], &rect[1], &rect[2], &rect[3]);
	            vswr_mode(window, 1);
	            int16_t rect2[4];
                rect2[0] = rect[0];
                rect2[1] = rect[1];
                rect2[2] = rect[0] + rect[2] - 1;
                rect2[3] = rect[1] + rect[3] - 1;
                
	            vr_recfl(screen_vhandle, rect2);

            break;
        }
	}
}

int main(int argc, char **argv)
{
	int16_t app_id = appl_init();
	int16_t gr_wchar, gr_hchar;
	int16_t gr_wbox, gr_hbox;
	
	//printf("\033E"); // clear screen

	if (app_id == -1) {
		Cconws("*** Initialization error.\n");
		Cconws("Press any key to continue.\n");
		Cconin();
		exit(1);
	}

	//printf("Application ID: 0x%08x\n", app_id);
	
	// Change mouse into pointer
	graf_mouse(0, NULL);
	
	screen_phandle = graf_handle(&gr_wchar, &gr_hchar, &gr_wbox, &gr_hbox);
	//printf("Screen phandle: 0x%08x\n", screen_phandle);
	screen_vhandle = open_vwork(screen_phandle);
	//printf("Screen vhandle: 0x%08x\n", screen_vhandle);
		
	//set_screen_attr();
	//printf("Resolution: %d\n", Getrez());
	//printf("Is the screen at... 0x%08x?\n",
	//  *((uint8_t *)0x80000));
	
	window = wind_create(0x2F, 50, 50, 640, 400);
	wind_open(window, 50, 50, 200, 100);
    int16_t rect[4];
    wind_get(window, 4, &rect[0], &rect[1], &rect[2], &rect[3]);
    vswr_mode(window, 1);
    int16_t rect2[4];
    rect2[0] = rect[0];
    rect2[1] = rect[1];
    rect2[2] = rect[0] + rect[2] - 1;
    rect2[3] = rect[1] + rect[3] - 1;

	vswr_mode(window, 1);
	vr_recfl(screen_vhandle, rect2);
	char *title = "SMONSON";
	wind_set(window, 2, (int32_t)title >> 16, (int32_t)title & 0xFFFF, 0, 0);

    event_handler();
	
	if (0) 
	{
	  //Cconws(test_string);
	  printf("Size of char is: %ld\n", sizeof(char));
	  printf("Size of short int is: %ld\n", sizeof(short int));
	  printf("Size of int is: %ld\n", sizeof(int));
	  printf("Size of long int is: %ld\n", sizeof(long int));
	  printf("Size of pointer int is: %ld\n", sizeof(void *));
	
	  //for (p = test_string; *p; p++)
		//  Cconout(*p);
		
	  printf("Hello %% Atari #%c.\n", '2');
	  printf("Hello %% Atari #%d.\n", 123456789);
	  printf("Hello %% Atari 0x%x.\n", 0x12345678);

	  printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	  char *buf = Malloc(32 * 1024);
	  printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	  Mfree(buf);
	  printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	
	  printf("Random: 0x%06x\n", Random());
	  printf("Random: 0x%06x\n", Random());
	  printf("Random: 0x%06x\n", Random());	
	
	  Cconin();
  }
  
  form_alert(1, "[1][Thanks!][ OK ]");
  
	/* End */
	//Cconin();
	v_clsvwk(screen_vhandle);
	appl_exit();
  
	return 0;
}
