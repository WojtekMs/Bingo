#include "bingo/Bingo.hpp"
#include "bingo/Board.hpp"

#include "test_utils.hpp"
#include "bingo/BingoData.hpp"

#include <gtest/gtest.h>
#include <random>

void assertUniqueColumn(const bingo::Board& bingo, const int col)
{
    const auto bingoCol = bingo.getColumn(col);
    ASSERT_TRUE(isUnique(bingoCol));
}

TEST(areDuplicateBingosTest,
     GivenNoBingoBoards_WhenAreDuplicateBingosCalled_ThenReturnFalse)
{
    std::vector<bingo::Board> bingos{};
    ASSERT_FALSE(bingo::areDuplicateBingos(bingos));
}

TEST(areDuplicateBingosTest,
     GivenDuplicateBingoBoards_WhenAreDuplicateBingosCalled_ThenReturnTrue)
{
    std::vector<bingo::Board> bingos{bingo::Board{bingo1}, bingo::Board{bingo1}};
    ASSERT_TRUE(bingo::areDuplicateBingos(bingos));
}

TEST(areDuplicateBingosTest,
     GivenDifferentBingoBoards_WhenAreDuplicateBingosCalled_ThenReturnFalse)
{
    std::vector<bingo::Board> bingos{bingo::Board{bingo1}, bingo::Board{bingo2}};
    ASSERT_FALSE(bingo::areDuplicateBingos(bingos));
}

TEST(makeRandomBingoTest,
     GivenMTEngine_WhenMakeRandomBingoCalled_ThenMakeBingoWithoutDuplicateValuesInColumns)
{
    std::random_device rd;
    std::mt19937 mt_engine{rd()};

    for (int i = 0; i < 1000; ++i) {
        const auto randomBingo = bingo::makeRandomBingoBoard(mt_engine);
        assertUniqueColumn(randomBingo, 0);
        assertUniqueColumn(randomBingo, 1);
        assertUniqueColumn(randomBingo, 2);
        assertUniqueColumn(randomBingo, 3);
        assertUniqueColumn(randomBingo, 4);
    }
}
