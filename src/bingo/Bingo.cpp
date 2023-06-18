#include "bingo/Bingo.hpp"

#include "bingo/Generator.hpp"

#include <fmt/format.h>
#include <vector>
namespace bingo
{
Board makeRandomBingoBoard(std::mt19937& mt_engine)
{
    Matrix<int> bingoNumbers(5, std::vector<int>(5));
    RandomUniqueNumberGenerator col0_gen{1, 15, mt_engine};
    RandomUniqueNumberGenerator col1_gen{16, 30, mt_engine};
    RandomUniqueNumberGenerator col2_gen{31, 45, mt_engine};
    RandomUniqueNumberGenerator col3_gen{46, 60, mt_engine};
    RandomUniqueNumberGenerator col4_gen{61, 75, mt_engine};

    for (size_t row = 0; row < bingoNumbers.size(); ++row) {
        for (size_t col = 0; col < bingoNumbers[row].size(); ++col) {
            auto number = 0;
            switch (col) {
                case 0:
                    number = col0_gen.getNext();
                    break;
                case 1:
                    number = col1_gen.getNext();
                    break;
                case 2:
                    number = col2_gen.getNext();
                    break;
                case 3:
                    number = col3_gen.getNext();
                    break;
                case 4:
                    number = col4_gen.getNext();
                    break;
            }
            bingoNumbers[row][col] = number;
        }
    }
    return Board(std::move(bingoNumbers));
}

bool areDuplicateBingos(const std::vector<Board>& bingos)
{
    for (size_t i = 0; i < bingos.size(); ++i) {
        for (size_t j = 0; j < bingos.size(); ++j) {
            if (i == j) {
                continue;
            }
            if (bingos[i] == bingos[j]) {
                fmt::print("Found duplicate bingo boards!\n");
                return true;
            }
        }
    }
    fmt::print("Did not find duplicate bingo boards!\n");
    return false;
}

std::vector<Board> makeUniqueRandomBingos(std::mt19937& mt_engine, const int count)
{
    const auto generateCountRandomBingos = [](std::mt19937& mt_engine, const int count) {
        std::vector<Board> result;
        for (int i = 0; i < count; ++i) {
            result.emplace_back(makeRandomBingoBoard(mt_engine));
        }
        return result;
    };
    auto result = generateCountRandomBingos(mt_engine, count);
    while (areDuplicateBingos(result)) {
        result.clear();
        result = generateCountRandomBingos(mt_engine, count);
    }
    return result;
}
}  // namespace bingo
