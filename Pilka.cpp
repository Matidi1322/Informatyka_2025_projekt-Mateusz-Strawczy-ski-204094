#include "Pilka.h"
#include <SFML/Graphics.hpp> 

void Pilka::bounceX() {
    vx = -vx;
}
void Pilka::bounceY() {
    vy = -vy;
}
void Pilka::collideWalls(float width, float height) {
    if (x - radius <= 0 || x + radius >= width)
    {
        bounceX();
        shape.setPosition(x, y);
    }

    if (y - radius <= 0)
    {
        bounceY();
        shape.setPosition(x, y);
    }
}
bool Pilka::collidePaddle(Paletka& p) {

    float Paddletop = p.getY() + (p.getWysokosc() / 2.f);
    float Paddleright = (p.getSzerokosc() / 2.f) + 15.f + p.getX();
    float Paddleleft = p.getX() - (p.getSzerokosc() / 2.f);

    if (x + radius <= Paddleright && x + radius >= Paddleleft && y + radius <= Paddletop + abs(vy) + 2.f && y + radius >= Paddletop)
    {
        vy = -std::abs(vy);
        y = (p.getY() - p.getWysokosc() / 2);
        shape.setPosition(x, y);
        return true;
    }
    return false;
}

void Pilka::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
    shape.setPosition(x, y);
}

void Pilka::setVelocity(float newVx, float newVy)
{
    vx = newVx;
    vy = newVy;
}