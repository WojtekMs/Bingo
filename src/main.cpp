#include "bingo/Bingo.hpp"
#include "drawer/BingoDrawer.hpp"
#include "parser/JsonParser.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <iostream>
#include <random>
#include <range/v3/view/enumerate.hpp>
#include <span>

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
    std::random_device random_device;
    std::mt19937 mt_engine{random_device()};
    const JsonParser parser;
    const auto config = parser.parseConfig(*content);
    drawer::BingoDrawer bingoDrawer(config);

    fmt::print("{}\n", config.toString());

    const auto bingoBoards =
        bingo::makeUniqueRandomBingos(mt_engine, config.generateBingosCount);
    for (const auto& [id, board] : ranges::views::enumerate(bingoBoards)) {
        const std::string filename = "bingo" + std::to_string(id) + ".jpg";
        const std::filesystem::path outputFile =
            config.generateBingosDirectory / filename;
        if (!bingoDrawer.saveToFile(board, outputFile)) {
            fmt::print("Could not save bingo {}", outputFile.string());
        }
    }
    return EXIT_SUCCESS;
}
