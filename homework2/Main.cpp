#include <iostream>
#include "logger.hpp"
#include "number_processor.hpp"
#include "safe_calculator.hpp"
#include "user.hpp"
#include "user_repository.hpp"

int main() {
    std::cout << "=== Демонстрация принципов проектирования на C++ ===\n" << std::endl;

    // 1. DRY - параметризованный логгер
    std::cout << "1. Принцип DRY (Logger):" << std::endl;
    Logger logger;
    logger.log("Тестовое сообщение об ошибке", LogLevel::Error);
    logger.log("Предупреждение", LogLevel::Warning);
    logger.log("Информация", LogLevel::Info);

    // 2. DRY - общая конфигурация
    std::cout << "\n2. Принцип DRY (Configuration):" << std::endl;
    DatabaseService dbService;
    dbService.connect();

    // 3. KISS - обработка чисел
    std::cout << "\n3. Принцип KISS (NumberProcessor):" << std::endl;
    NumberProcessor processor;
    processor.printPositiveNumbers({-5, 0, 3, 7, -2, 10});

    // 4. KISS - безопасное деление
    std::cout << "\n4. Принцип KISS (SafeCalculator):" << std::endl;
    SafeCalculator calculator;
    auto result = calculator.divide(10, 2);
    if (result.has_value()) {
        std::cout << "10 / 2 = " << result.value() << std::endl;
    }

    // 5. YAGNI - разделение ответственности
    std::cout << "\n5. Принцип YAGNI (User/Repository):" << std::endl;
    User user{1, "Алексей Петров", "alex@example.com"};
    UserRepository userRepo;
    userRepo.save(user);

    std::cout << "\n=== Программа завершена ===" << std::endl;

    return 0;
}