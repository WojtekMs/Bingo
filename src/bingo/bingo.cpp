#include "bingo/bingo.hpp"

#include "bingo/generator.hpp"

#include <vector>

Matrix<int> make_random_bingo()
{
    Matrix<int> bingo1(5, std::vector<int>(5));
    RandomUniqueNumberGenerator col0_gen{1, 15};
    RandomUniqueNumberGenerator col1_gen{16, 30};
    RandomUniqueNumberGenerator col2_gen{31, 45};
    RandomUniqueNumberGenerator col3_gen{46, 60};
    RandomUniqueNumberGenerator col4_gen{61, 75};

    for (size_t row = 0; row < bingo1.size(); ++row) {
        for (size_t col = 0; col < bingo1[row].size(); ++col) {
            auto number = 0;
            switch (col) {
                case 0:
                    number = col0_gen.getNext();
                    break;
                case 1:
                    number = col1_gen.getNext();
                    break;
                case 2:
                    number = col2_gen.getNext();
                    break;
                case 3:
                    number = col3_gen.getNext();
                    break;
                case 4:
                    number = col4_gen.getNext();
                    break;
            }
            bingo1[row][col] = number;
        }
    }
    return bingo1;
}
