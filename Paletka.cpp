#include "Paletka.h"
#include <SFML/Graphics.hpp> 

void Paletka::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        moveRight();
    }
}

void Paletka::moveLeft() {
    x = x - predkosc;
    shape.setPosition(x, y);
}
void Paletka::moveRight() {
    x = x + predkosc;
    shape.setPosition(x, y);
}

void Paletka::clampToBounds(float width) {
    if (x - szerokosc / 2 < 0)
        x = szerokosc / 2;
    if (x + szerokosc / 2 > width)
        x = width - szerokosc / 2;
    shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}

void Paletka::setPosition(const sf::Vector2f& pos)
{
    x = pos.x;
    y = pos.y;
    shape.setPosition(x, y);
}