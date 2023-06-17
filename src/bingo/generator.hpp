#pragma once

#include <numeric>
#include <random>
#include <vector>

class RandomUniqueNumberGenerator
{
   public:
    RandomUniqueNumberGenerator(const int begin, const int end)
    {
        numbers.resize(end - begin + 1);
        std::iota(numbers.begin(), numbers.end(), begin);
        std::shuffle(numbers.begin(), numbers.end(), std::mt19937{r()});
    }

    int getNext()
    {
        int number = numbers.back();
        numbers.pop_back();
        return number;
    }

   private:
    std::vector<int> numbers;
    std::random_device r;
};
