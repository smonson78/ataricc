#ifndef MENU_H_
#define MENU_H_

#include "MenuItem.h"
#include "LinkedList.h"

class Menu {
public:
	Menu();
	Menu(const char *title);
	void addMenuItem(const char *text, menu_callback callback);
	virtual ~Menu();
	const char *getTitle() {
		return title;
	}
	smonson::LinkedList<MenuItem> *getContents() {
		return &contents;
	}
private:
	const char *title;
	smonson::LinkedList<MenuItem> contents;
};

#endif
