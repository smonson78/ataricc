#ifndef MENUBAR_H_
#define MENUBAR_H_

extern "C" {
#include "aes_object.h"
}
#include "Menu.h"
#include "LinkedList.h"

class MenuBar {
public:
	MenuBar();
	virtual ~MenuBar();
	void addMenu(Menu *menu);
	OBJECT *buildObjectArray();
//private:
	smonson::LinkedList<Menu> contents;
};

#endif
