#pragma once

#include <optional>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include "parser/Config.hpp"

[[nodiscard]] std::optional<std::string> readFile(const std::string& fileName) noexcept;
void display(std::vector<std::reference_wrapper<sf::Drawable>> sprites);
bool loadBingoBoard(const Config& config, sf::Texture& bingoTexture);
bool loadFont(sf::Font& font);
sf::Text drawNumber(const Config& config, const int row, const int col, const int number);
void composeAndSaveToFile(sf::Texture& bingoTexture,
                          std::vector<std::reference_wrapper<sf::Drawable>> drawables,
                          std::filesystem::path file);
