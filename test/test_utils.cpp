#include "test_utils.hpp"

#include <filesystem>
#include <stdexcept>

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
