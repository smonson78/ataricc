
extern "C" {
#include <gemdos.h>
#include <libc.h>
}

#include "app.h"
#include "LinkedListNode.h"


void show_malloc()
{
    struct memblock_t *p = malloc_head;
    printf("\n");
    while (p) {
        if (p->prev)
            printf("%p <-- ", p->prev);
        else
            printf("    null <-- ", p->prev);
        
        if (p->used)
        	printf("%p (%d) (USED)", p, p->size);
        else
        	printf("%p (%d)", p, p->size);

        if (p->next)
            printf(" --> %p", p->next);
        else
            printf(" --> null", p->next);
 
        printf("\n");
        p = p->next;
    }
    printf("\n");
}


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

void recurse_print(OBJECT *b, int start)
{
	OBJECT *o = &b[start];
	printf("%d - type %d -->%d [%d .. %d] \n",
		start, o->ob_type,
		o->ob_next == -1 ? -1 : o->ob_next, o->ob_head, o->ob_tail);
	if (o->ob_head != -1) {
		int n = o->ob_head;
		while (n != start) {
			recurse_print(b, n);
			n = b[n].ob_next;
		}
	}
}

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
	
	MenuBar menubar;
	Menu programMenu(" Smonson ");
	Menu fileMenu(" File ");
	menubar.addMenu(&programMenu);
	menubar.addMenu(&fileMenu);

	programMenu.addMenuItem("  About...  ", (menu_callback)NULL);
	programMenu.addMenuItem("------------", (menu_callback)NULL);
	programMenu.addMenuItem("", (menu_callback)NULL);
	programMenu.addMenuItem("", (menu_callback)NULL);
	programMenu.addMenuItem("", (menu_callback)NULL);
	programMenu.addMenuItem("", (menu_callback)NULL);
	programMenu.addMenuItem("", (menu_callback)NULL);
	programMenu.addMenuItem("", (menu_callback)NULL);

	fileMenu.addMenuItem("  Open  ", (menu_callback)NULL);
	fileMenu.addMenuItem("  Close  ", (menu_callback)NULL);
	fileMenu.addMenuItem("---------", (menu_callback)NULL);

	fileMenu.addMenuItem("  Quit  ", (menu_callback)NULL);

	OBJECT *o = menubar.buildObjectArray();
	menu_bar(o, MENU_SHOW);

	//recurse_print(o, 0);

	//Cnecin();
    // Main loop
    app.run();
    delete[] o;
   
    delete simon2;
    return 0;
}
