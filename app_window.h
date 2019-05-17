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

    public:
    bool maximised;
    int16_t dimensions[4]; // current dimensions
    int16_t isopen;
    const char *title;

    protected:
    int16_t nm_dimensions[4]; // dimensions saved while maximised
    int16_t style;

    public:
    Window();
    virtual ~Window();
    void set_app(Application *a); // called by application on setup
    void settitle(const char *t);
    void setstyle(int16_t s);

    void update();
    void size(int16_t x, int16_t y, int16_t w, int16_t h);
    void redraw(int16_t vhandle, int16_t x, int16_t y, int16_t w, int16_t h);
    void redraw_window();

    void open();
    void close();

    // Redraw application client area after being obscured
    virtual void draw(int16_t vhandle, int16_t rect[]);
    virtual void event_closed();
    virtual void event_topped();
    virtual void event_fulled();
    virtual void event_resized();
};

#endif
