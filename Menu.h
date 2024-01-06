#ifndef MENU_H_
#define MENU_H_

#include "MenuItem.h"
#include "LinkedList.h"

class Menu {
public:
	Menu();
	Menu(const char *title);
	void addMenuItem(const char *text);
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

	// For use of OBJECT-array handling:
private:
	int title_object;
public:
	void set_object_index(int index);
	int get_object_index();

};

#endif
