extern "C" {
#include <tos.h>
#include <aes.h>
#include <aes_window.h>
#include <libc.h>
}

#include "app_app.h"

class SmonsonWindow : public Window {
    public:
    SmonsonWindow(Application &a) : Window(a) {
    }

    void draw(int16_t vhandle, int16_t rect[]) {
        //printf("draw(): handle is %d\n", vhandle);
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
    
    void close() {
        app.quit();
    }
};

int main(int argc, char **argv)
{
    Application app;
	
	SmonsonWindow simon(app);
	simon.settitle("Smonson");
	simon.size(300, 50, 200, 150);
	app.add_window(&simon);

	Window simon2(app);
	simon2.settitle("Not-smonson");
	simon2.size(400, 80, 200, 150);
	app.add_window(&simon2);

	simon2.open();
	simon.open();

    // Main loop	
    app.run();
  
    form_alert(1, "[1][Thanks!][ OK ]");
  
	return 0;
}
