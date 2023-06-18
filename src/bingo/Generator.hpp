#pragma once

#include <numeric>
#include <random>
#include <vector>
#include <stdexcept>

class RandomUniqueNumberGenerator
{
   public:
    RandomUniqueNumberGenerator(const int begin, const int end, std::mt19937& mt_engine)
    {
        numbers.resize(end - begin + 1);
        std::iota(numbers.begin(), numbers.end(), begin);
        std::shuffle(numbers.begin(), numbers.end(), mt_engine);
    }

    int getNext()
    {
        if (numbers.empty()) {
            throw std::runtime_error("Generator run out of values");
        }
        int number = numbers.back();
        numbers.pop_back();
        return number;
    }

   private:
    std::vector<int> numbers;
};
