#include "bingo/bingo.hpp"
#include "parser/JsonParser.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <span>
#include <iostream>

sf::Texture bingoTexture;
sf::Font font;

void print_bingo(const Matrix<int>& bingo, int index) {
    std::cout << "Bingo nr " << index << "\n";
    for (auto& row : bingo) {
        for (auto& val : row) {
            std::cout << std::setw(2) << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n";
    std::cout << std::endl;
}

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
    fmt::print("Generating bingo\n");
    const auto bingoBoard = make_random_bingo();
    print_bingo(bingoBoard, 1);
    int id = 1;
    const std::string filename = "bingo" + std::to_string(id) + ".jpg";
    const std::filesystem::path outputFile = config.generateBingosDirectory / filename;
    fmt::print("Drawing {}\n", outputFile.string());
    drawBingo(bingoBoard, bingoTexture, config, font, outputFile);

    return EXIT_SUCCESS;
}
