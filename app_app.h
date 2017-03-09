#ifndef __APP_APP_H
#define __APP_APP_H

extern "C" {
#include <stdint.h>
#include <libc.h>
}

#include "aes_object.h"

#include "app_window.h"

#define MAX_WINDOWS 16

typedef struct {
    int16_t x, y, w, h;
} RectXYWH;

class Application {

    public:
	int16_t app_id;

    private:
	int16_t gr_wchar, gr_hchar, gr_wbox, gr_hbox;
    int16_t screen_phandle;
    int16_t screen_vhandle;
	bool quit_flag;
	Window *windows[MAX_WINDOWS];
    OBJECT tree[17];

    public:
    Application();
    ~Application();
    
    void add_window(Window *w);
    void quit();
    void run();
    
    void get_screen_size(RectXYWH *rect);
        
    private:
    int16_t open_vwork(int16_t phys_handle);
    Window *find_window_by_handle(int16_t h);
};

#endif

