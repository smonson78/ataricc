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
    int16_t visible[4]; // work area
    
    private:
    bool maximised;
    int16_t dimensions[4];

    int16_t isopen;
    const char *title;
        
    public:
    Window();
    void set_app(Application *a);
    
    void settitle(const char *t);

    void size(int16_t x, int16_t y, int16_t w, int16_t h);
    void update();
    void redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h);

    virtual void open();
    virtual void close();
    
    virtual void draw(int16_t vhandle, int16_t rect[]);
    virtual void topped();
    virtual void fulled();
    
    
    
};

#endif
