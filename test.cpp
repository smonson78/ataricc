
extern "C" {
#include <gem.h>
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


int main(int argc, char **argv)
{
	Application app;
	
	SmonsonWindow simon;
	simon.setstyle(WIND_BASIC);
	simon.settitle("Smonson");
	simon.size(350, 50, 200, 150);
	app.add_window(&simon);

	//Window *simon2 = new Window();
	//app.add_window(simon2);
	//simon2->setstyle(WIND_NAME|WIND_MOVER);
	//simon2->settitle("Not-smonson");
	//simon2->size(400, 80, 200, 150);

	//simon2->open();
	simon.open();
	
	MenuBar menubar;
	Menu programMenu("Smonson");
	Menu fileMenu("File");
	menubar.addMenu(&programMenu);
	menubar.addMenu(&fileMenu);

	smonson::LinkedListNode<Menu> *p = menubar.contents.getHead();
	//printf("menubar head is %p\n", p);
	//p = new smonson::LinkedListNode<Menu>((Menu *)0);

	//void *x = malloc(44);
	//p = (smonson::LinkedListNode<Menu> *)malloc(32);
	//printf("p is %p\n", p);
	//while (p) {
	//	Menu *item = p->getItem();
	//	printf(" * %s\n", item->getTitle());
	//	p = p->getNext();
	//}
	//show_malloc();
	//MenuItem about("About...", (menu_callback)0);
	//ProgramMenu.addMenuItem("Your Message");
    // Main loop
    app.run();
   
    //delete simon2;
    return 0;
}
