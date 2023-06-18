#pragma once

#include "bingo/Types.hpp"

#include <vector>

namespace bingo
{
void validateBoardNumbers(const Matrix<int>& numbers);

class Board
{
   public:
    Board() = default;
    explicit Board(Matrix<int> numbers);

    int getWidth() const;
    int getHeight() const;
    int getNumber(int row, int col) const;
    std::vector<int> getColumn(int col) const;

    bool operator==(const Board& board) const = default;

   private:
    int height_{0};
    int width_{0};
    Matrix<int> board_{};
};
}  // namespace bingo
