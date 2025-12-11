#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones, int score, int lives);
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, int& score, int& lives);

private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
    int savedScore;
    int savedLives;
};