/*
 Temat projektu : Gra arkanoide
 Zakres indywidualny: Gra polega na zbiciu wsztskich klocków za pomocą piłki, której nie pozwalamy spaść,
 poprzez sterowanie paletką od której piłka się odbija. Mamy 3 życia oraz możliwośc zapisu gry oraz jej wczytania.
*/

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h" 

enum class StanGry { Menu, Playing, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    StanGry currentState = StanGry::Menu;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == StanGry::Menu)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.moveUp();
                    if (event.key.code == sf::Keyboard::Down)
                        menu.moveDown();
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (menu.getSelectedItem() == 0) // Nowa Gra
                        {
                            game.reset();
                            currentState = StanGry::Playing;
                        }
                        else if (menu.getSelectedItem() == 1) // Wczytaj gre
                        {
                            if (game.loadGame())
                            {
                                currentState = StanGry::Playing;
                            }
                        }
                        else if (menu.getSelectedItem() == 2) // Wyjscie
                        {
                            window.close();
                        }
                    }
                }
            }
            else if (currentState == StanGry::Playing)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        sf::Time dt = clock.restart();

        if (currentState == StanGry::Menu)
        {
            window.clear();
            menu.draw(window);
            window.display();
        }
        else if (currentState == StanGry::Playing)
        {
            window.clear();
            game.update(dt);

            if (game.isGameOver())
            {
                currentState = StanGry::Menu;
            }

            game.render(window);
            window.display();
        }
    }

    return 0;
}