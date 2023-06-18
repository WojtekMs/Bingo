#include "bingo/Board.hpp"
#include "bingo/Types.hpp"

#include <random>
#include <vector>
namespace bingo
{
Board makeRandomBingoBoard(std::mt19937& mt_engine);
bool areDuplicateBingos(const std::vector<Board>& bingos);
std::vector<Board> makeUniqueRandomBingos(std::mt19937& mt_engine, int count);
}  // namespace bingo
