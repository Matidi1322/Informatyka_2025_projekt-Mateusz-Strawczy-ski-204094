#include "GameState.h"
#include <fstream>
#include <iostream>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, int score, int lives)
{
    paddlePosition = sf::Vector2f(p.getX(), p.getY());
    ballPosition = sf::Vector2f(b.getX(), b.getY());
    ballVelocity = sf::Vector2f(b.getVx(), b.getVy());

    savedScore = score;
    savedLives = lives;

    blocks.clear();
    for (const auto& stone : stones)
    {
        BlockData data;
        data.x = stone.getPosition().x;
        data.y = stone.getPosition().y;
        data.hp = stone.getHP();
        blocks.push_back(data);
    }
}

bool GameState::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    file << "SCORE " << savedScore << "\n";
    file << "LIVES " << savedLives << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    std::cout << "Gra zapisana!" << std::endl;
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;

    if (!(file >> label >> paddlePosition.x >> paddlePosition.y) || label != "PADDLE") return false;

    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) || label != "BALL") return false;

    if (!(file >> label >> savedScore) || label != "SCORE") return false;

    if (!(file >> label >> savedLives) || label != "LIVES") return false;

    int blocksCount;
    if (!(file >> label >> blocksCount) || label != "BLOCKS_COUNT") return false;

    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        BlockData data;
        file >> data.x >> data.y >> data.hp;
        blocks.push_back(data);
    }

    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, int& score, int& lives)
{
    p.setPosition(paddlePosition);

    b.setPosition(ballPosition.x, ballPosition.y);
    b.setVelocity(ballVelocity.x, ballVelocity.y);

    score = savedScore;
    lives = savedLives;

    stones.clear();

    const float SZEROKOSC = 800.f;
    const int ILOSC_KOLUMN = 6;
    const float ROZMIAR_BLOKU_X = (SZEROKOSC - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    const float ROZMIAR_BLOKU_Y = 25.f;

    sf::Vector2f size(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y);

    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), size, data.hp);
    }
}