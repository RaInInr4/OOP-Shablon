#include <iostream>
#include <vector>

class NumberProcessor {
public:
    void printPositiveNumbers(const std::vector<int>& numbers) {
        if (numbers.empty()) {
            std::cout << "Массив пуст" << std::endl;
            return;
        }

        std::cout << "Положительные числа:" << std::endl;
        for (int number : numbers) {
            if (number > 0) {
                std::cout << number << std::endl;
            }
        }
    }
};

