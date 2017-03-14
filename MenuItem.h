#ifndef MENUITEM_H_
#define MENUITEM_H_

typedef void (*menu_callback)();

class MenuItem {
public:
	MenuItem(const char* text, menu_callback action);
	virtual ~MenuItem();
private:
	const char *text;
	menu_callback action;
};

#endif
