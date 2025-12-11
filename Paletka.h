#pragma once
#include <SFML/Graphics.hpp> 

class Paletka
{
public:
    Paletka(float x_in, float y_in, float szer_in, float wys_in, float predkosc_in)
        : x(x_in), y(y_in), szerokosc(szer_in), wysokosc(wys_in), predkosc(predkosc_in) {
        shape.setSize({ szerokosc, wysokosc });
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Red);
    }

    void move();
    void moveLeft();
    void moveRight();
    void clampToBounds(float width);
    void draw(sf::RenderTarget& target);

    void setPosition(const sf::Vector2f& pos);

    float getX() const { return x; };
    float getY() const { return y; };
    float getSzerokosc() const { return szerokosc; };
    float getWysokosc() const { return wysokosc; };
    float getPredkosc() const { return predkosc; };

private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;
};