#include "Game.h"
#include <SFML/Graphics.hpp> 
#include <cstdlib> 
#include <iostream>

Game::Game()
    : m_paletka(320.f, 500.f, 100.f, 20.f, 12.f),
    m_pilka(320.f, 450.f, 5.f, -6.f, 6.f)
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Blad wczytywania czcionki arial.ttf!" << std::endl;
    }

    m_textScore.setFont(m_font);
    m_textScore.setCharacterSize(20);
    m_textScore.setFillColor(sf::Color::White);
    m_textScore.setPosition(10.f, 10.f);

    m_lifeIcon.setPointCount(3);
    m_lifeIcon.setPoint(0, sf::Vector2f(0.f, -12.f));
    m_lifeIcon.setPoint(1, sf::Vector2f(10.f, 10.f));
    m_lifeIcon.setPoint(2, sf::Vector2f(-10.f, 10.f));

    m_lifeIcon.setFillColor(sf::Color::Green);
    m_lifeIcon.setOutlineColor(sf::Color::White);
    m_lifeIcon.setOutlineThickness(1.f);
    m_lifeIcon.setOrigin(0.f, 0.f);

    reset();
}

void Game::reset()
{
    m_isGameOver = false;
    m_score = 0;
    m_lives = 3;

    m_textScore.setString("Punkty: 0");

    m_paletka = Paletka(320.f, 500.f, 100.f, 20.f, 10.f);
    m_pilka = Pilka(320.f, 450.f, 5.f, -6.f, 8.f);

    m_bloki.clear();

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float SZEROKOSC = 800.f;
    const float ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; y++)
    {
        for (int x = 0; x < ILOSC_KOLUMN; x++)
        {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = 50.f + y * (ROZMIAR_BLOKU_Y + 2.f);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::update(sf::Time dt)
{
    if (m_isGameOver) return;

    m_lifeIcon.rotate(2.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        saveGame();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(800.f);
    m_pilka.move();

    if (m_pilka.getY() > 600.f)
    {
        m_lives--;
        if (m_lives > 0)
        {
            m_pilka.setPosition(320.f, 450.f);
            m_pilka.setVelocity(5.f, -6.f);
        }
        else
        {
            m_isGameOver = true;
        }
    }

    m_textScore.setString("Punkty: " + std::to_string(m_score));

    m_pilka.collideWalls(800.f, 600.f);
    m_pilka.collidePaddle(m_paletka);

    for (int i = 0; i < m_bloki.size(); i++)
    {
        if (m_bloki[i].isDestroyed()) continue;

        sf::Vector2f pos = m_bloki[i].getPosition();
        sf::Vector2f size = m_bloki[i].getSize();
        float x = m_pilka.getX();
        float y = m_pilka.getY();
        float r = m_pilka.getRadius();

        if (x + r > pos.x && x - r < pos.x + size.x &&
            y + r > pos.y && y - r < pos.y + size.y)
        {
            m_pilka.bounceY();
            m_bloki[i].trafienie();

            if (m_bloki[i].isDestroyed())
            {
                m_score += 1;
                m_bloki.erase(m_bloki.begin() + i);
                i--;
            }
            break;
        }
    }
}

void Game::render(sf::RenderTarget& target)
{
    for (const auto& b : m_bloki)
        b.draw(target);

    m_paletka.draw(target);
    m_pilka.draw(target);

    target.draw(m_textScore);

    for (int i = 0; i < m_lives; i++)
    {
        m_lifeIcon.setPosition(750.f - (i * 30.f), 30.f);
        target.draw(m_lifeIcon);
    }
}

void Game::saveGame()
{
    GameState gameState;
    gameState.capture(m_paletka, m_pilka, m_bloki, m_score, m_lives);
    gameState.saveToFile("zapis.txt");
}

bool Game::loadGame()
{
    GameState gameState;
    if (gameState.loadFromFile("zapis.txt"))
    {
        gameState.apply(m_paletka, m_pilka, m_bloki, m_score, m_lives);
        m_isGameOver = false;
        return true;
    }
    std::cout << "Nie udalo sie wczytac gry!" << std::endl;
    return false;
}