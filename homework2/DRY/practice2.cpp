#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class User {
public:
    std::string name;
    std::string email;
    std::string role;

    User(const std::string& name, const std::string& email, const std::string& role)
        : name(name), email(email), role(role) {}
};

class UserManager {
private:
    std::vector<User> users;

    // DRY: Общий метод для поиска пользователя по email
    User* findUserByEmail(const std::string& email) {
        for (auto& user : users) {
            if (user.email == email) {
                return &user;
            }
        }
        return nullptr;
    }

public:
    // Добавление пользователя
    bool addUser(const User& user) {
        if (findUserByEmail(user.email) != nullptr) {
            return false; // Пользователь с таким email уже существует
        }
        users.push_back(user);
        return true;
    }

    // Удаление пользователя
    bool removeUser(const std::string& email) {
        auto it = std::remove_if(users.begin(), users.end(),
            [&email](const User& user) { return user.email == email; });
        
        if (it != users.end()) {
            users.erase(it, users.end());
            return true;
        }
        return false;
    }

    // Обновление пользователя
    bool updateUser(const std::string& email, const std::string& newName, const std::string& newRole) {
        User* user = findUserByEmail(email);
        if (user == nullptr) {
            return false;
        }
        
        user->name = newName;
        user->role = newRole;
        return true;
    }

    // Получение всех пользователей
    std::vector<User> getAllUsers() const {
        return users;
    }

    // Получение количества пользователей
    size_t getUserCount() const {
        return users.size();
    }
};

void printUsers(const std::vector<User>& users) {
    std::cout << "\n=== Список пользователей ===" << std::endl;
    if (users.empty()) {
        std::cout << "Пользователей нет." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << i + 1 << ". Имя: " << users[i].name 
                  << ", Email: " << users[i].email 
                  << ", Роль: " << users[i].role 
                  << std::endl;
    }
    std::cout << "============================\n" << std::endl;
}

int main() {
    UserManager manager;
    
    std::cout << "=== Система управления пользователями ===" << std::endl;
    
    // Добавление пользователей
    std::cout << "\nДобавляем пользователей..." << std::endl;
    
    bool added1 = manager.addUser(User("Иван Иванов", "ivan@example.com", "Admin"));
    if (added1) {
        std::cout << "✓ Пользователь Иван Иванов добавлен" << std::endl;
    } else {
        std::cout << "✗ Ошибка добавления пользователя" << std::endl;
    }
    
    bool added2 = manager.addUser(User("Петр Петров", "petr@example.com", "User"));
    if (added2) {
        std::cout << "✓ Пользователь Петр Петров добавлен" << std::endl;
    } else {
        std::cout << "✗ Ошибка добавления пользователя" << std::endl;
    }
    
    // Попытка добавить пользователя с существующим email
    bool added3 = manager.addUser(User("Иван Дубов", "ivan@example.com", "User"));
    if (!added3) {
        std::cout << "✓ Правильно отклонена попытка добавить пользователя с существующим email" << std::endl;
    }
    
    printUsers(manager.getAllUsers());
    
    // Обновление пользователя
    std::cout << "Обновляем пользователя ivan@example.com..." << std::endl;
    bool updated = manager.updateUser("ivan@example.com", "Иван Сидоров", "SuperAdmin");
    if (updated) {
        std::cout << "✓ Пользователь обновлен" << std::endl;
    } else {
        std::cout << "✗ Пользователь не найден" << std::endl;
    }
    
    printUsers(manager.getAllUsers());
    
    // Удаление пользователя
    std::cout << "Удаляем пользователя petr@example.com..." << std::endl;
    bool removed = manager.removeUser("petr@example.com");
    if (removed) {
        std::cout << "✓ Пользователь удален" << std::endl;
    } else {
        std::cout << "✗ Пользователь не найден" << std::endl;
    }
    
    printUsers(manager.getAllUsers());
    
    // Попытка удалить несуществующего пользователя
    std::cout << "Пытаемся удалить несуществующего пользователя..." << std::endl;
    bool removedFake = manager.removeUser("fake@example.com");
    if (!removedFake) {
        std::cout << "✓ Правильно отклонена попытка удалить несуществующего пользователя" << std::endl;
    }
    
    // Добавляем еще пользователей для демонстрации
    manager.addUser(User("Анна Смирнова", "anna@example.com", "Manager"));
    manager.addUser(User("Сергей Козлов", "sergey@example.com", "User"));
    
    std::cout << "\nИтоговое состояние системы:" << std::endl;
    std::cout << "Всего пользователей: " << manager.getUserCount() << std::endl;
    printUsers(manager.getAllUsers());
    
    return 0;
}