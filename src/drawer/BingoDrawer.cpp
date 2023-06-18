#include "drawer/BingoDrawer.hpp"

#include <fmt/format.h>
#include <stdexcept>

namespace drawer
{
BingoDrawer::BingoDrawer(const Config& config) : config_(config)
{
    const int boardWidth = config.boardUpperRightCorner.x - config.boardUpperLeftCorner.x;
    const int boardHeight = boardWidth;
    sf::IntRect boardRect{config.boardUpperLeftCorner.x,
                          config.boardUpperLeftCorner.y,
                          boardWidth,
                          boardHeight};
    if (!bingoTexture_.loadFromFile(config.originalBingoBoardFile.string())) {
        const std::string errorMsg{fmt::format("Could not read texture: {}\n",
                                               config.originalBingoBoardFile.string())};
        fmt::print(stderr, fmt::runtime(errorMsg));
        throw std::runtime_error(errorMsg);
    }
    fmt::print("Texture loaded\n");

    if (!font_.loadFromFile(config.fontFile.string())) {
        const std::string errorMsg{
            fmt::format("Could not read font: {}\n", config.fontFile.string())};
        fmt::print(stderr, fmt::runtime(errorMsg));
        throw std::runtime_error(errorMsg);
    }
    fmt::print("Font loaded\n");

    bingoSprite_.setTexture(bingoTexture_);
    rTexture_.create(bingoTexture_.getSize().x, bingoTexture_.getSize().y);
}

sf::Text BingoDrawer::drawNumber(const bingo::Board& board, int row, int col)
{
    sf::Text text(std::to_string(board.getNumber(row, col)),
                  font_,
                  config_.generatedNumbersFontSize);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Style::Regular);

    // set origin
    sf::Vector2f size{text.getGlobalBounds().width, text.getGlobalBounds().height};
    sf::Vector2f position{text.getLocalBounds().left, text.getLocalBounds().top};
    text.setOrigin(size / 2.f + position);

    // calculate position
    const int boardSquares = board.getWidth();
    const int linesCount = boardSquares + 1;
    const int boardWidthPixels =
        config_.boardUpperRightCorner.x - config_.boardUpperLeftCorner.x;
    const float squareWidth =
        (boardWidthPixels - (linesCount * config_.linePixelWidth)) / boardSquares;
    const float squareHeight = squareWidth;
    const float numberX = config_.boardUpperLeftCorner.x +
                          ((col + 1) * config_.linePixelWidth) + (col * squareWidth);
    const float numberY = config_.boardUpperLeftCorner.y +
                          ((row + 1) * config_.linePixelWidth) + (row * squareHeight);
    text.setPosition(sf::Vector2f{numberX, numberY} +
                     sf::Vector2f{squareWidth, squareHeight} / 2.f);
    return text;
}

bool BingoDrawer::saveToFile(const bingo::Board& board, std::filesystem::path outputFile)
{
    // Prepare numbers on the board
    std::vector<sf::Text> numbers{};
    for (int row = 0; row < board.getHeight(); ++row) {
        for (int col = 0; col < board.getWidth(); ++col) {
            numbers.emplace_back(drawNumber(board, row, col));
        }
    }
    // Create ready bingo board texture
    rTexture_.clear();
    rTexture_.draw(bingoSprite_);
    for (auto& number : numbers) {
        rTexture_.draw(number);
    }
    rTexture_.display();
    // Save texture to a file
    fmt::print("Saving {}\n", outputFile.string());
    const auto image = rTexture_.getTexture().copyToImage();
    return image.saveToFile(outputFile.string());
}
}  // namespace drawer
