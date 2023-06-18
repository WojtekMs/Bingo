#pragma once

#include <string>
#include <vector>
#include "bingo/Bingo.hpp"

std::string readTestData(const std::string& filename);
std::vector<int> getColumn(const Matrix<int>& bingo, int col);
bool isUnique(const std::vector<int>& values);
