#include <string>

class Configuration {
public:
    static Configuration& getInstance() {
        static Configuration instance;
        return instance;
    }

    std::string getDatabaseConnectionString() const { return databaseConnectionString; }
    std::string getApiBaseUrl() const { return apiBaseUrl; }
    int getTimeoutSeconds() const { return timeoutSeconds; }

    // Удаляем копирование и присваивание
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

private:
    Configuration() : 
        databaseConnectionString("Server=myServer;Database=myDb;User Id=myUser;Password=myPass;"),
        apiBaseUrl("https://api.example.com"),
        timeoutSeconds(30) {}

    std::string databaseConnectionString;
    std::string apiBaseUrl;
    int timeoutSeconds;
};

// Сервисы используют общие настройки
class DatabaseService {
public:
    void connect() {
        std::string connectionString = Configuration::getInstance().getDatabaseConnectionString();
        // Логика подключения
        std::cout << "Подключение к БД: " << connectionString << std::endl;
    }
};

class ApiService {
public:
    void callApi() {
        std::string url = Configuration::getInstance().getApiBaseUrl();
        // Логика API вызова
        std::cout << "Вызов API: " << url << std::endl;
    }
};