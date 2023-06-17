#include "utils.hpp"

#include <fmt/format.h>
#include <fstream>
#include <sstream>

std::optional<std::string> readFile(const std::string& fileName) noexcept
{
    std::ifstream stream(fileName);
    if (!stream.good()) {
        return std::nullopt;
    }
    std::stringstream str;
    str << stream.rdbuf();
    return str.str();
}
void display(std::vector<std::reference_wrapper<sf::Drawable>> sprites)
{
    sf::RenderWindow mWindow(sf::VideoMode(800, 600), "Bingo");
    while (mWindow.isOpen()) {
        sf::Event event{};
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                mWindow.close();
            }
        }
        // draw
        mWindow.clear();
        for (auto& sprite : sprites) {
            mWindow.draw(sprite.get());
        }
        mWindow.display();
    }
}

bool loadBingoBoard(const Config& config, sf::Texture& bingoTexture)
{
    const int boardWidth = config.boardUpperRightCorner.x - config.boardUpperLeftCorner.x;
    const int boardHeight = boardWidth;
    sf::IntRect boardRect{config.boardUpperLeftCorner.x,
                          config.boardUpperLeftCorner.y,
                          boardWidth,
                          boardHeight};
    if (!bingoTexture.loadFromFile(config.originalBingoBoardFile.string())) {
        fmt::print(stderr,
                   "Could not read texture: {}\n",
                   config.originalBingoBoardFile.string());
        return false;
    }
    fmt::print("Texture loaded\n");
    return true;
}

bool loadFont(sf::Font& font)
{
    std::string fontPath{"../assets/DejaVuSans.ttf"};
    if (!font.loadFromFile(fontPath)) {
        fmt::print(stderr, "Could not read font: {}\n", fontPath);
        return false;
    }
    return true;
}

sf::Text drawNumber(const Config& config, const int row, const int col, const int number)
{
    constexpr int characterSize = 170;
    sf::Text text(std::to_string(number), font, characterSize);
    text.setFillColor(sf::Color::Black);

    // set origin 
    sf::Vector2f size{text.getGlobalBounds().width, text.getGlobalBounds().height};
    sf::Vector2f position{text.getLocalBounds().left, text.getLocalBounds().top};
    text.setOrigin(size / 2.f + position);
    // calculate position
    constexpr int boardSquares = 5;
    constexpr int linesCount = boardSquares + 1;
    const int boardWidth = config.boardUpperRightCorner.x - config.boardUpperLeftCorner.x;
    const float squareWidth =
        (boardWidth - (linesCount * config.linePixelWidth)) / boardSquares;
    const float squareHeight = squareWidth;
    const float numberX = config.boardUpperLeftCorner.x +
                          (col + 1 * config.linePixelWidth) + (col * squareWidth);
    const float numberY = config.boardUpperLeftCorner.y +
                          (row + 1 * config.linePixelWidth) + (row * squareWidth);
    text.setPosition(sf::Vector2f{numberX, numberY} + sf::Vector2f{squareWidth, squareHeight} / 2.f);
    return text;
}

void composeAndSaveToFile(sf::Texture& bingoTexture,
                          std::vector<std::reference_wrapper<sf::Drawable>> drawables,
                          std::filesystem::path file)
{
    sf::RenderTexture rtexture;
    auto size = bingoTexture.getSize();
    rtexture.create(size.x, size.y);
    for (auto& drawable : drawables) {
        rtexture.draw(drawable.get());
    }
    rtexture.display();
    fmt::print("saving {}\n", file.string());
    auto texture = rtexture.getTexture();
    auto image = texture.copyToImage();
    image.saveToFile(file.string());
}
