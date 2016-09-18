#ifndef __APP_WINDOW_H
#define __APP_WINDOW_H

extern "C" {
#include <aes.h>
#include <aes_window.h>
#include <tos.h>
#include <stdint.h>
}


class Window {
    public:
    int16_t handle;
    
    Window() {
        handle = wind_create(0x2F, 50, 50, 640, 400);
    }
    
    void settitle(const char *title) {
	    wind_set(handle, 2, 
	        (int32_t)title >> 16, (int32_t)title & 0xFFFF, 0, 0);
    }
    
    void open() {
        wind_open(handle, 200, 100, 200, 100);
    }
    
    void size(int16_t x, int16_t y, int16_t w, int16_t h) {
        wind_set(handle, 5/*WF_CURRXYWH*/, x, y, w, h);
    }
    
    void redraw(int16_t vhandle);
    void redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h);

};


#endif
