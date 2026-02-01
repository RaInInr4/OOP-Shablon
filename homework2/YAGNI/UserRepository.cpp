#include <iostream>
#include <string>

class User {
public:
    int id;
    std::string name;
    std::string email;
};

// Отдельный класс для работы с хранилищем
class UserRepository {
public:
    void save(const User& user) {
        // Простая логика сохранения
        std::cout << "Сохранен пользователь: " << user.name << std::endl;
        // Реальная логика: подключение к БД, SQL-запрос и т.д.
    }

    User getById(int id) {
        // Логика получения пользователя
        return User{id, "Тестовый пользователь", "test@example.com"};
    }
};

// Отдельный класс для email-рассылок (если это понадобится позже)
class EmailService {
public:
    void sendWelcomeEmail(const std::string& email) {
        // Логика отправки email
        std::cout << "Отправлено приветственное письмо на " << email << std::endl;
    }
};