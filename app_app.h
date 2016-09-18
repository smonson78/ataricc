#ifndef __APP_APP_H
#define __APP_APP_H

extern "C" {
#include <stdint.h>
#include <libc.h>
}

#include "app_window.h"

#define MAX_WINDOWS 7

class Application {

    public:
	int16_t app_id;
    int16_t screen_phandle;
    int16_t screen_vhandle;

    private:
	int16_t gr_wchar, gr_hchar;
	int16_t gr_wbox, gr_hbox;
	
	Window *windows[MAX_WINDOWS];

    public:
    Application() {
    
        // Clear window list
        for (int16_t i = 0; i < MAX_WINDOWS; i++)
            windows[i] = (Window *)NULL;
        
        app_id = appl_init();
	    if (app_id == -1) {
		    Cconws("*** Initialization error.\n");
		    Cconws("Press any key to continue.\n");
		    Cconin();
		    exit(1);
	    }
	    
	    // Change mouse from busy-bee into pointer
	    graf_mouse(0, (MFORM*)NULL);
	
	    screen_phandle = graf_handle(&gr_wchar, &gr_hchar, &gr_wbox, &gr_hbox);
	    screen_vhandle = open_vwork(screen_phandle);
    }
    
    ~Application() {
	    v_clsvwk(screen_vhandle);
	    appl_exit();
    }
    
    void add_window(Window *w) {
        // Keep track of the given window
        for (int16_t i = 0; i < MAX_WINDOWS; i++) {
            if (!windows[i]) {
                windows[i] = w;
                return;
            }
        }
        
        // FIXME: handle error
    }
    
    Window *find_window_by_handle(int16_t h);
    void event_handler();
    
    private:
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

};

#endif

