extern "C" {
#include <tos.h>
#include <aes.h>
#include <aes_window.h>
#include <libc.h>
}

class Application {
    public:
	int16_t app_id;
    int16_t screen_phandle;
    int16_t screen_vhandle;

    private:
	int16_t gr_wchar, gr_hchar;
	int16_t gr_wbox, gr_hbox;

    public:
    Application() {
        app_id = appl_init();
	    if (app_id == -1) {
		    Cconws("*** Initialization error.\n");
		    Cconws("Press any key to continue.\n");
		    Cconin();
		    exit(1);
	    }
	    
	    // Change mouse into pointer
	    graf_mouse(0, (MFORM*)NULL);
	
	    screen_phandle = graf_handle(&gr_wchar, &gr_hchar, &gr_wbox, &gr_hbox);
	    screen_vhandle = open_vwork(screen_phandle);
    }
    
    ~Application() {
	    /* End */
	    //Cconin();
	    v_clsvwk(screen_vhandle);
	    appl_exit();
    }
    
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

class Window {
    private:
    int16_t handle;
    Application *app;
    
    public:
    Window(Application *a) {
        app = a;
        handle = wind_create(0x2F, 50, 50, 640, 400);
    }
    
    void settitle(const char *title) {
	    wind_set(handle, 2, 
	        (int32_t)title >> 16, (int32_t)title & 0xFFFF, 0, 0);
    }
    
    void open() {
        wind_open(handle, 200, 100, 200, 100);
    }
    
    void redraw() {
        int16_t rect[4];

        // Get extent of visible area
        wind_get(handle, 4, // WF_WORKXYWH
            &rect[0], &rect[1], &rect[2], &rect[3]);

        // Set draw mode=REPLACE
        vswr_mode(handle, 1);
        
        // Calculate new x,y,w,h from rect corners
        int16_t rect2[4];
        rect2[0] = rect[0];
        rect2[1] = rect[1];
        rect2[2] = rect[0] + rect[2] - 1;
        rect2[3] = rect[1] + rect[3] - 1;
        
        // fill
    	vswr_mode(handle, 1);
        vr_recfl(app->screen_vhandle, rect2);
    }
};

void event_handler(Window *simon)
{
	int16_t quit = 0;
	int16_t msg[8];

    int16_t rect[4];
	while (!quit) {

        evnt_mesag(msg);
        
        switch (msg[0]) {
        case 22: // WM_CLOSED
            //if (msg[3] == window)
                quit = 1;
            break;
        case 23: // WM_FULLED
            // get size of widow 0 (desktop)

            wind_get(0, 4, &rect[0], &rect[1], &rect[2], &rect[3]);

            wind_set(msg[3], 5/*WF_CURRXYWH*/,
                rect[0], rect[1], rect[2], rect[3]);
            simon->redraw();
            break;
        case 28: // WM_MOVED
            wind_set(msg[3], 5/*WF_CURRXYWH*/,
                msg[4], msg[5], msg[6], msg[7]);
            simon->redraw();
            break;
        case 27: // WM_SIZED
            wind_set(msg[3], 5/*WF_CURRXYWH*/,
                msg[4], msg[5], msg[6], msg[7]);
	        simon->redraw();

            break;
        }
	}
}

int main(int argc, char **argv)
{
    Application app;
    
	//printf("\033E"); // clear screen

	
	Window simon(&app);
	simon.settitle("Smonson");
	simon.open();
	simon.redraw();
	
    event_handler(&simon);
  
    form_alert(1, "[1][Thanks!][ OK ]");
  
	return 0;
}
