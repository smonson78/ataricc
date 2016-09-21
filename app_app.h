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
    Application();
    ~Application();
    
    void add_window(Window *w);
    
    Window *find_window_by_handle(int16_t h);
    void event_handler();
    
    private:
    int16_t open_vwork(int16_t phys_handle);
};

#endif

