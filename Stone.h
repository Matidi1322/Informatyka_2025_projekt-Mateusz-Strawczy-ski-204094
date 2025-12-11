#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape
{
public:
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);

    void trafienie();
    bool isDestroyed() const;
    void draw(sf::RenderTarget& target) const;
    int getHP() const;

private:
    void aktualizujKolor();

    int m_punktyZycia;
    bool m_jestZniszczony;

    static const std::array<sf::Color, 4> m_colorLUT;
};