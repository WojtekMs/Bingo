#include "bingo/Board.hpp"

#include <range/v3/view/enumerate.hpp>
#include <set>
#include <stdexcept>

namespace bingo
{
void validateBoardNumbers(const Matrix<int>& numbers)
{
    std::set<size_t> rowSizes;
    for (const auto& row : numbers) {
        rowSizes.insert(row.size());
    }
    if (rowSizes.size() != 1) {
        throw std::invalid_argument("All rows in bingo board must have the same size");
    }
}
Board::Board(Matrix<int> numbers)
{
    validateBoardNumbers(numbers);
    height_ = numbers.size();
    if (height_ != 0) {
        width_ = numbers.front().size();
    } else {
        width_ = 0;
    }
    board_ = std::move(numbers);
}

int Board::getWidth() const
{
    return width_;
}
int Board::getHeight() const
{
    return height_;
}

int Board::getNumber(const int row, const int col) const
{
    if (row < 0 || row > height_) {
        throw std::invalid_argument("Row must be in range <0; height)");
    }
    if (col < 0 || col > width_) {
        throw std::invalid_argument("Cold must be in range <0; width)");
    }
    return board_[row][col];
}

std::vector<int> Board::getColumn(int col) const
{
    constexpr int minColumnsId = 0;
    if (col < minColumnsId || col > width_) {
        return {};
    }
    std::vector<int> column(height_);
    for (const auto& [rowId, rowNumbers] : ranges::views::enumerate(board_)) {
        column[rowId] = rowNumbers[col];
    }
    return column;
}

}  // namespace bingo
