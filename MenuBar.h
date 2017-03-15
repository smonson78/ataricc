#ifndef MENUBAR_H_
#define MENUBAR_H_

#include <Menu.h>
#include "LinkedList.h"

class MenuBar {
public:
	MenuBar();
	virtual ~MenuBar();
	void addMenu(Menu *menu);
private:
	smonson::LinkedList<Menu> contents;
};

#endif
