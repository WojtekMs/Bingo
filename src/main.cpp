#include "parser/JsonParser.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <span>

sf::Texture bingoTexture;
sf::Font font;

int main(const int argc, const char** argv)
{
    const std::span<const char*> args(argv, argc);
    if (args.size() != 2) {
        fmt::print(stderr, "usage: {} config.json\n", args.front());
        return EXIT_FAILURE;
    }
    // TODO: Add protection from path traversal
    const auto content = readFile(args.back());
    if (!content) {
        fmt::print(stderr, "could not read file: {}\n", args.back());
        return EXIT_FAILURE;
    }
    const JsonParser parser;
    const auto config = parser.parseConfig(*content);
    fmt::print("{}\n", config.toString());

    // read the graphics
    if (!loadBingoBoard(config, bingoTexture)) {
        return EXIT_FAILURE;
    }
    if (!loadFont(font)) {
        return EXIT_FAILURE;
    }
    sf::Sprite bingoSprite(bingoTexture);
    // bingoSprite.scale(sf::Vector2f{0.1, 0.1});


    // create a number
    auto text = drawNumber(config, 0, 0, 1);
    auto text2 = drawNumber(config, 0, 1, 10);
    auto text3 = drawNumber(config, 0, 2, 20);
    auto text4 = drawNumber(config, 1, 0, 2);
    auto text5 = drawNumber(config, 2, 0, 3);
    composeAndSaveToFile(bingoTexture,
                         {bingoSprite, text, text2, text3, text4, text5},
                         config.generateBingosDirectory / "bingo1.jpg");

    return EXIT_SUCCESS;
}
