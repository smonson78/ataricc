#ifndef __APP_WINDOW_H
#define __APP_WINDOW_H

extern "C" {
#include <aes.h>
#include <aes_window.h>
#include <tos.h>
#include <stdint.h>
}

class Application;

class Window {
    public:
    int16_t handle;

    protected:
    Application *app;
    int16_t visible[4]; // cached work area
    
    private:
    bool maximised;
    int16_t dimensions[4]; // current dimensions
    int16_t nm_dimensions[4]; // dimensions saved while maximised
    int16_t style;
    int16_t isopen;
    const char *title;
        
    public:
    Window();
    virtual ~Window();
    void set_app(Application *a); // called by application on setup
    void settitle(const char *t);
    void setstyle(int16_t s);

    void size(int16_t x, int16_t y, int16_t w, int16_t h);
    void update();
    void redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h);

    void open();
    void close();
    
    virtual void event_closed();
    virtual void draw(int16_t vhandle, int16_t rect[]);
    virtual void event_topped();
    virtual void event_fulled();
    
    
    
};

#endif
