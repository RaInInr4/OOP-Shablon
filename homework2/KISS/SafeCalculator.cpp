#include <iostream>
#include <optional>

class SafeCalculator {
public:
    std::optional<int> divide(int dividend, int divisor) {
        if (divisor == 0) {
            std::cout << "Ошибка: деление на ноль" << std::endl;
            return std::nullopt;
        }
        return dividend / divisor;
    }

    // Альтернативный вариант с Try-паттерном
    bool tryDivide(int dividend, int divisor, int& result) {
        if (divisor == 0) {
            return false;
        }
        result = dividend / divisor;
        return true;
    }
};
