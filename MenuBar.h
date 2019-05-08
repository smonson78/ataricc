#ifndef MENUBAR_H_
#define MENUBAR_H_

extern "C" {
#include "aes_object.h"
}
#include "Menu.h"
#include "app.h"
#include "LinkedList.h"

#include "Menu.h"

class MenuBar {
public:
	MenuBar();
	virtual ~MenuBar();
	void addMenu(Menu *menu);
	OBJECT *buildObjectArray(Application *app);
//private:
	smonson::LinkedList<Menu> contents;
	void new_object2(Application *app, OBJECT *o, uint16_t type, void *spec, uint16_t x,
		uint16_t y_lines, uint16_t y_pixels, uint16_t width,
		uint16_t height_lines, uint16_t height_pixels);
};

#endif
