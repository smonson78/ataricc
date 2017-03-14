#ifndef MENUBAR_H_
#define MENUBAR_H_

#include <vector>

class MenuBar {
public:
	MenuBar();
	virtual ~MenuBar();
private:
	std::vector<Menu> contents;
};

#endif
