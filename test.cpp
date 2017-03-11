extern "C" {
#include <tos.h>
#include <aes.h>
#include <aes_window.h>
#include <libc.h>
}

#include "app_app.h"

class SmonsonWindow : public Window {

    void draw(int16_t vhandle, int16_t rect[]) {
        vsf_color(vhandle, 1);
        v_bar(vhandle, rect);
        vsf_color(vhandle, 0);
        v_ellipse(vhandle, 
            (visible[0] + visible[2] / 2),
            (visible[1] + visible[3] / 2),
            visible[2] / 2,
            visible[3] / 2
        );
    }
    
    void event_closed() {
        int16_t response = form_alert(1, 
            "[2][Are you sure you want to quit?]"
            "[ NO | YES ]");
        if (response == 2)
            app->quit();
    }
};

void *operator new(size_t n)
{
    printf("operator new\n");
    return malloc(n);
}

void *operator new[] (size_t n)
{
    return ::operator new(n);
}

void operator delete(void *p)
{
    printf("operator delete\n");
    free(p);
}

void operator delete[] (void *p)
{
    ::operator delete(p);
}

void operator delete(void *p, size_t n)
{
    ::operator delete(p);
}

void operator delete[] (void *p, size_t n)
{
    ::operator delete(p);
}

/*
typedef void (*func_ptr) (void);
extern func_ptr __CTOR_END__[];
extern func_ptr __DTOR_LIST__[];

void __do_global_ctors_aux () {
	func_ptr *p;
	for (p = __CTOR_END__ - 1; *p != (func_ptr) -1; p--)
		(*p)(); 
}

void __do_global_dtors_aux ()
{
  func_ptr *p;
  for (p = __DTOR_LIST__ + 1; *p; p++)
    (*p) ();
}
*/

int main(int argc, char **argv)
{
    Application app;
	
	SmonsonWindow simon;
	simon.setstyle(WIND_BASIC);
	simon.settitle("Smonson");
	simon.size(350, 50, 200, 150);
	app.add_window(&simon);

	Window *simon2 = new Window();
	app.add_window(simon2);
	simon2->setstyle(WIND_NAME|WIND_MOVER);
	simon2->settitle("Not-smonson");
	simon2->size(400, 80, 200, 150);

	simon2->open();
	simon.open();
	
    // Main loop	
    app.run();
    
    delete simon2;
    
    return 0;
}
