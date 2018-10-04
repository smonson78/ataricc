#ifndef MENUBAR_H_
#define MENUBAR_H_

extern "C" {
#include "aes_object.h"
}
#include "Menu.h"
#include "LinkedList.h"

#include "Menu.h"

class MenuBar {
public:
	MenuBar(uint16_t char_height);
	virtual ~MenuBar();
	void addMenu(Menu *menu);
	OBJECT *buildObjectArray();
//private:
	smonson::LinkedList<Menu> contents;
	void new_object2(OBJECT *o, uint16_t type, void *spec, uint16_t x,
		uint16_t y_lines, uint16_t y_pixels, uint16_t width,
		uint16_t height_lines, uint16_t height_pixels);
		
	uint8_t char_height;

};

#endif
