#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Blad wczytywania czcionki arial.ttf!" << std::endl;
	}

	menuItems[0].setFont(font);
	menuItems[0].setFillColor(sf::Color::Red);
	menuItems[0].setString("Nowa Gra");
	menuItems[0].setPosition(sf::Vector2f(width / 2.f - 50.f, height / (MAX_ITEMS + 1) * 1));

	menuItems[1].setFont(font);
	menuItems[1].setFillColor(sf::Color::White);
	menuItems[1].setString("Wczytaj gre");
	menuItems[1].setPosition(sf::Vector2f(width / 2.f - 60.f, height / (MAX_ITEMS + 1) * 2));

	menuItems[2].setFont(font);
	menuItems[2].setFillColor(sf::Color::White);
	menuItems[2].setString("Wyjscie");
	menuItems[2].setPosition(sf::Vector2f(width / 2.f - 40.f, height / (MAX_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menuItems[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menuItems[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_ITEMS)
	{
		menuItems[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}