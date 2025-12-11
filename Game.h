#pragma once
#include <SFML/Graphics.hpp> 
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h" 
#include "GameState.h"

class Game {
public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);

    bool isGameOver() const { return m_isGameOver; }
    void reset();

    void saveGame();
    bool loadGame();

    int getScore() const { return m_score; }
    int getLives() const { return m_lives; }

private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;
    bool m_isGameOver;

    int m_score;
    int m_lives;

    sf::Font m_font;
    sf::Text m_textScore;
    sf::ConvexShape m_lifeIcon;
};