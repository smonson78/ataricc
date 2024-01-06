#ifndef MENUITEM_H_
#define MENUITEM_H_

typedef void (*menu_callback)();

class MenuItem {
public:
	MenuItem(const char* text, menu_callback action);
	virtual ~MenuItem();
	const char *getText() {
		return text;
	}
	const menu_callback getAction() {
		return action;
	}
private:
	const char *text;
	menu_callback action;
};

#endif
