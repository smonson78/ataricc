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
    
    private:
    int16_t dimensions[4];
    int16_t visible[4];
    int16_t isopen;
    const char *title;
        
    public:
    Window() {
        isopen = false;
        handle = wind_create(0x2F, 0, 0, 640, 400);
    }
    
    void settitle(const char *t) {
        title = t;
	    wind_set(handle, 2, 
	        (int32_t)t >> 16, (int32_t)t & 0xFFFF, 0, 0);
    }
    
    void open() {
        update();
        //graf_mouse(256 /* M_OFF */, (MFORM *)NULL);
        wind_open(handle, dimensions[0], dimensions[1], 
            dimensions[2], dimensions[3]);
        //graf_mouse(257 /* M_ON */, (MFORM *)NULL);
        isopen = true;
    }
    
    void size(int16_t x, int16_t y, int16_t w, int16_t h);
    void update();
    
    void redraw(int16_t vhandle);
    void redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h);
    void topped();
    void fulled();
};


#endif
