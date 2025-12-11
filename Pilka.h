#pragma once
#include <SFML/Graphics.hpp> 
#include "Paletka.h"

class Pilka
{
public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in)
        : x(x_in), y(y_in), vx(vx_in), vy(vy_in), radius(r_in) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }
    void move() {
        x += vx;
        y += vy;
        shape.setPosition(x, y);
    }
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collidePaddle(Paletka& p);
    void draw(sf::RenderTarget& target) { target.draw(shape); };

    void setPosition(float newX, float newY);
    void setVelocity(float newVx, float newVy);

    float getX() const { return x; };
    float getY() const { return y; };
    float getVx() const { return vx; };
    float getVy() const { return vy; };
    float getRadius() const { return radius; };
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;
};