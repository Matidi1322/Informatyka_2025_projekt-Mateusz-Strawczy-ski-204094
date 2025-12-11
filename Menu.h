#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define MAX_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getSelectedItem() const { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuItems[MAX_ITEMS];
};