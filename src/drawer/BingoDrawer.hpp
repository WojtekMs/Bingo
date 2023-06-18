#pragma once

#include "bingo/Board.hpp"
#include "parser/Config.hpp"

#include <SFML/Graphics.hpp>
#include <filesystem>

namespace drawer
{
class BingoDrawer
{
   public:
    explicit BingoDrawer(const Config& config);

    bool saveToFile(const bingo::Board& board, std::filesystem::path outputFile);

   private:
    sf::Text drawNumber(const bingo::Board& board, int row, int col);

    sf::Texture bingoTexture_;
    sf::RenderTexture rTexture_;
    sf::Font font_;
    sf::Sprite bingoSprite_;
    Config config_;
};

}  // namespace drawer
