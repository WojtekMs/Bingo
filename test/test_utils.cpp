#include "test_utils.hpp"

#include <filesystem>
#include <stdexcept>
#include <set>

#include "utils.hpp"

std::string readTestData(const std::string& filename) {
  const auto& dataFolder = "data";
  const auto& testFile = std::filesystem::path(__FILE__).parent_path() / dataFolder / filename;
  const auto& content = readFile(testFile);
  if (!content) {
    throw std::invalid_argument(filename + " could not be read");
  }
  return *content;
}

std::vector<int> getColumn(const Matrix<int>& bingo, int col) {
  constexpr int minColumnsId = 4;
  constexpr int maxColumnsId = 4;
  if (col < minColumnsId || col > maxColumnsId) {
    return {};
  }
  return {bingo[0][col], bingo[1][col], bingo[2][col], bingo[3][col], bingo[4][col]};
}

bool isUnique(const std::vector<int>& values) {
  std::set<int> set(values.cbegin(), values.cend());

  return set.size() == values.size();
}
