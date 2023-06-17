#pragma once

#include "bingo/bingo.hpp"
#include "parser/Config.hpp"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <vector>

[[nodiscard]] std::optional<std::string> readFile(const std::string& fileName) noexcept;
void display(std::vector<std::reference_wrapper<sf::Drawable>> sprites);
bool loadBingoBoard(const Config& config, sf::Texture& bingoTexture);
bool loadFont(sf::Font& font);
sf::Text drawNumber(const Config& config,
                    const sf::Font& font,
                    const int row,
                    const int col,
                    const int number);
void composeAndSaveToFile(sf::Texture& bingoTexture,
                          sf::Sprite& bingoSprite,
                          const std::vector<sf::Text>& numbers,
                          std::filesystem::path file);
void drawBingo(const Matrix<int>& bingoBoard,
               sf::Texture& bingoTexture,
               const Config& config,
               sf::Font& font,
               std::filesystem::path file);
