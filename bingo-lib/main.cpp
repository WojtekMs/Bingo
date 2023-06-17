#include <functional>
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iomanip>

std::random_device r;
std::default_random_engine e1(r());
std::vector<std::uniform_int_distribution<int>> col_dist{std::uniform_int_distribution<int>{1, 15}, 
                                                         std::uniform_int_distribution<int>{16, 30},
                                                         std::uniform_int_distribution<int>{31, 45},
                                                         std::uniform_int_distribution<int>{46, 60},
                                                         std::uniform_int_distribution<int>{61, 75}};

std::vector<int> bingo_numbers(75, 0);


// Square Matrix
template<typename T>
using Matrix = std::vector<std::vector<T>>;


template <typename T>
class ColView {
    public:
    ColView(const Matrix<T>& matrix, const int col) : matrix_(matrix), col_(col) {
        if (!matrix.empty() && col >= matrix.size()) {
            throw std::invalid_argument("Cannot create ColView because matrix is too small");
        }
    }
    bool operator==(const ColView<T>& rhs) {
        auto& rhs_matrix = rhs.matrix_.get();
        auto& matrix = matrix_.get();
        for (int row = 0; row < rhs_matrix.size(); ++row) {
            if (matrix[row][col_] != rhs_matrix[row][col_]) {
                return false;
            }
        }
        return true;
    }

    bool is_bingo() {
        auto& matrix = matrix_.get();
        int sum = 0;
        for (int row = 0; row < matrix.size(); ++row) {
            sum += matrix[row][col_];
        }
        return sum == 0;
    }

    private:
    std::reference_wrapper<const Matrix<T>> matrix_;
    int col_;
};

bool find_in_col(const Matrix<int>& bingo, const int col, const int number) {
    for (int row = 0; row < bingo.size(); ++row) {
        if (bingo[row][col] == number) {
            return true;
        }
    }
    return false;
}

Matrix<int> make_random_bingo() {
    Matrix<int> bingo1(5, std::vector<int>(5));
    for (int row = 0; row < bingo1.size(); ++row) {
        for (int col = 0; col < bingo1[row].size(); ++col) {
            auto number = col_dist[col](e1);
            while (find_in_col(bingo1, col, number)) {
                number = col_dist[col](e1);
            }
            bingo1[row][col] = number;
        }

    }
    return bingo1;
}

bool are_duplicate_bingos(const std::vector<Matrix<int>>& bingos) {
    for (int i = 0; i < bingos.size(); ++i) {
        for (int j = 0; j < bingos.size(); ++j) {
            if (i == j) {
                continue;
            }
            if (bingos[i] == bingos[j]) {
                std::cout << "Found duplicate bingo boards!\n";
                return true;
            }
        }
    }
    std::cout << "Did not find duplicate bingo boards!\n";
    return false;
}

int draw_number() {
    int number = bingo_numbers.back();
    bingo_numbers.pop_back();
    return number;
}


void cross_number(Matrix<int>& bingo, const int number) {
    for (auto& row : bingo) {
        auto it = std::find(row.begin(), row.end(), number);
        if (it != row.end()) {
            // cross out the number
            *it = 0;
        }
    }
}

bool is_first_winner(const Matrix<int>& bingo) {
    for (auto& row : bingo) {
        if (std::accumulate(row.begin(), row.end(), 0) == 0) {
            return true;
        }   
    }
    // Square Matrix!
    for (int col = 0; col < bingo.size(); ++col) {
        ColView col_view(bingo, col);
        if (col_view.is_bingo()) {
            return true;
        }        
    }
    int axis1_sum = 0;
    for (int row = 0, col = 0; row < bingo.size(); ++row, ++col) {
        axis1_sum += bingo[row][col];
    }
    if (axis1_sum == 0) {
        return true;
    }
    int axis2_sum = 0;
    for (int row = bingo.size() - 1, col = bingo.size() - 1; row >= 0; --row, --col) {
        axis2_sum += bingo[row][col];
    }
    if (axis2_sum == 0) {
        return true;
    }
    return false;
}

bool is_full_house(const Matrix<int>& bingo) {
    int sum = 0;
    for (auto& row : bingo) {
        sum += std::accumulate(row.begin(), row.end(), 0);        
    }
    return sum == 0;
}

void print_bingo(const Matrix<int>& bingo, int index) {
    std::cout << "Bingo nr " << index << "\n";
    for (auto& row : bingo) {
        for (auto& val : row) {
            std::cout << std::setw(2) << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n";
}

void print_numbers(const std::vector<int>& numbers) {
    std::cout << "Drawn " << numbers.size() << " numbers: [";
    for (auto number : numbers) {
        std::cout << number << ", ";
    }
    std::cout << "]\n";
}


int main() {
    std::vector<int> drawn_numbers{};
    std::vector<int> winners{};
    bool first_winner = false;
    constexpr int bingos_count = 116;
    std::iota(bingo_numbers.begin(), bingo_numbers.end(), 1);
    std::shuffle(bingo_numbers.begin(), bingo_numbers.end(), std::mt19937{r()});
    std::vector<Matrix<int>> bingos;
    for (int i = 0; i < bingos_count; ++i) {
        bingos.emplace_back(make_random_bingo());
    }
    std::vector<Matrix<int>> bingos_copy = bingos;

    if (!are_duplicate_bingos(bingos)) {
        // play bingo !
        while(!first_winner) {
            const int number = draw_number();
            drawn_numbers.push_back(number);
            for (auto& bingo : bingos) {
                cross_number(bingo, number);
            }
            for (int i = 0; i < bingos.size(); ++i) {
                if (is_full_house(bingos[i])) {
                    std::cout << "Bingo nr " << i << " is the winner of 1st phase\n";
                    winners.push_back(i);
                    first_winner = true;
                }
            }
        }

    }
    print_numbers(drawn_numbers);
    for (auto winner_id : winners) {
        print_bingo(bingos_copy[winner_id], winner_id);
    }

    return EXIT_SUCCESS;
}

