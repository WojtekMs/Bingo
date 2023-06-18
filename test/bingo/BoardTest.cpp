#include "bingo/Bingo.hpp"
#include "bingo/BingoData.hpp"
#include "bingo/Board.hpp"
#include "test_utils.hpp"

#include <gtest/gtest.h>
#include <random>

class BoardTest : public ::testing::Test
{
   protected:
    bingo::Board board{bingo1};
};

TEST_F(BoardTest, GivenMatrix_WhenGet0Column_ThenReturn0Column)
{
    const std::vector<int> expectedColumn{1, 2, 3, 4, 5};

    ASSERT_EQ(expectedColumn, board.getColumn(0));
}

TEST_F(BoardTest, GivenMatrix_WhenGet2Column_ThenReturn2Column)
{
    const std::vector<int> expectedColumn{31, 32, 33, 34, 35};

    ASSERT_EQ(expectedColumn, board.getColumn(2));
}

TEST_F(BoardTest, GivenMatrix_WhenGet10Column_ThenReturnEmpty)
{
    const std::vector<int> expectedColumn{};

    ASSERT_EQ(expectedColumn, board.getColumn(10));
}

TEST_F(BoardTest, GivenMatrix_WhenGetHeight_ThenReturn5)
{
    constexpr int expectedHeight{5};

    ASSERT_EQ(expectedHeight, board.getHeight());
}

TEST_F(BoardTest, GivenMatrix_WhenGetWidth_ThenReturn5)
{
    constexpr int expectedWidth{5};

    ASSERT_EQ(expectedWidth, board.getWidth());
}

TEST_F(BoardTest, GivenEqualBoards_WhenOperatorEqualCalled_ThenReturnTrue)
{
    const bingo::Board board2{bingo1};

    ASSERT_EQ(board, board2);
    ASSERT_TRUE(board == board2);
}

TEST_F(BoardTest, GivenNotEqualBoards_WhenOperatorEqualCalled_ThenReturnFalse)
{
    const bingo::Board board2{bingo2};

    ASSERT_NE(board, board2);
    ASSERT_FALSE(board == board2);
}

TEST_F(BoardTest, GivenMatrix_WhenGetNumber_ThenReturnNumber)
{
    ASSERT_EQ(board.getNumber(0, 0), 1);
    ASSERT_EQ(board.getNumber(0, 1), 16);
    ASSERT_EQ(board.getNumber(1, 0), 2);
}
