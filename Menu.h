#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Menu();
	Menu(const char *title);
	//void addMenuItem(const char *text, menu_callback callback);
	virtual ~Menu();
private:
	const char *title;
};

#endif
