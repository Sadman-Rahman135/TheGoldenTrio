#pragma once
#include "stdafx.h"

#define MAX_MENU 4
class Menu
{
public:
	sf::RenderWindow MENU;
	
	void setMenu(int width, int	 height);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	int menuPressed()
	{
		return menuSelected;
	}

	~Menu();

private:
	int menuSelected;
	sf::Font font;
	sf::Text menu[MAX_MENU];
};
