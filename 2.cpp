#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    int quantity;
    
public:
    // Конструктор
    Book(const std::string& title, const std::string& author, 
         const std::string& isbn, int quantity)
        : title(title), author(author), isbn(isbn), quantity(quantity) {}
    
    // Геттеры
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
    int getQuantity() const { return quantity; }
    
    // Увеличить количество экземпляров
    void increaseQuantity(int amount = 1) {
        quantity += amount;
    }
    
    // Уменьшить количество экземпляров
    bool decreaseQuantity(int amount = 1) {
        if (quantity >= amount) {
            quantity -= amount;
            return true;
        }
        return false;
    }
    
    // Проверка доступности
    bool isAvailable() const {
        return quantity > 0;
    }
    
    // Вывод информации о книге
    void displayInfo() const {
        std::cout << "'" << title << "' - " << author 
                  << " (ISBN: " << isbn << "), доступно: " << quantity << std::endl;
    }
};

class Reader {
private:
    std::string name;
    int readerId;
    std::vector<std::string> borrowedBooks; // ISBN взятых книг
    
public:
    // Конструктор
    Reader(const std::string& name, int readerId)
        : name(name), readerId(readerId) {}
    
    // Геттеры
    std::string getName() const { return name; }
    int getReaderId() const { return readerId; }
    const std::vector<std::string>& getBorrowedBooks() const { return borrowedBooks; }
    
    // Взять книгу
    void borrowBook(const std::string& isbn) {
        borrowedBooks.push_back(isbn);
    }
    
    // Вернуть книгу
    bool returnBook(const std::string& isbn) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == isbn) {
                borrowedBooks.erase(it);
                return true;
            }
        }
        return false;
    }
    
    // Проверить, взял ли читатель книгу
    bool hasBook(const std::string& isbn) const {
        for (const auto& bookIsbn : borrowedBooks) {
            if (bookIsbn == isbn) {
                return true;
            }
        }
        return false;
    }
    
    // Вывод информации о читателе
    void displayInfo() const {
        std::cout << "Читатель: " << name << " (ID: " << readerId << ")" << std::endl;
        if (!borrowedBooks.empty()) {
            std::cout << "  Взятые книги (ISBN): ";
            for (const auto& isbn : borrowedBooks) {
                std::cout << isbn << " ";
            }
            std::cout << std::endl;
        }
    }
};

class Library {
private:
    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<Reader>> readers;
    std::map<int, std::string> borrowingRecords; // ID читателя -> ISBN книги (для простоты)
    
public:
    // Добавление книги
    void addBook(const std::string& title, const std::string& author, 
                 const std::string& isbn, int quantity) {
        // Проверяем, есть ли уже книга с таким ISBN
        for (const auto& book : books) {
            if (book->getISBN() == isbn) {
                book->increaseQuantity(quantity);
                std::cout << "Количество книги '" << title << "' увеличено на " << quantity << std::endl;
                return;
            }
        }
        
        // Если книги нет, добавляем новую
        auto newBook = std::make_shared<Book>(title, author, isbn, quantity);
        books.push_back(newBook);
        std::cout << "Книга '" << title << "' добавлена в библиотеку" << std::endl;
    }
    
    // Удаление книги или уменьшение количества
    bool removeBook(const std::string& isbn, int quantity = 1) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getISBN() == isbn) {
                if ((*it)->decreaseQuantity(quantity)) {
                    std::cout << "Количество книги '" << (*it)->getTitle() 
                              << "' уменьшено на " << quantity << std::endl;
                    
                    // Если количество стало 0, можно удалить книгу из каталога
                    if ((*it)->getQuantity() == 0) {
                        // Проверяем, не взята ли книга кем-то
                        bool isBorrowed = false;
                        for (const auto& reader : readers) {
                            if (reader->hasBook(isbn)) {
                                isBorrowed = true;
                                break;
                            }
                        }
                        
                        if (!isBorrowed) {
                            books.erase(it);
                            std::cout << "Книга '" << (*it)->getTitle() 
                                      << "' удалена из каталога (нет экземпляров)" << std::endl;
                        } else {
                            std::cout << "Книга '" << (*it)->getTitle() 
                                      << "' осталась в каталоге (взята читателями)" << std::endl;
                        }
                    }
                    return true;
                } else {
                    std::cout << "Недостаточно экземпляров для удаления" << std::endl;
                    return false;
                }
            }
        }
        std::cout << "Книга с ISBN " << isbn << " не найдена" << std::endl;
        return false;
    }
    
    // Регистрация читателя
    void registerReader(const std::string& name, int readerId) {
        // Проверяем, есть ли уже читатель с таким ID
        for (const auto& reader : readers) {
            if (reader->getReaderId() == readerId) {
                std::cout << "Читатель с ID " << readerId << " уже зарегистрирован" << std::endl;
                return;
            }
        }
        
        auto newReader = std::make_shared<Reader>(name, readerId);
        readers.push_back(newReader);
        std::cout << "Читатель " << name << " зарегистрирован с ID " << readerId << std::endl;
    }
    
    // Удаление читателя
    bool removeReader(int readerId) {
        for (auto it = readers.begin(); it != readers.end(); ++it) {
            if ((*it)->getReaderId() == readerId) {
                // Проверяем, вернул ли читатель все книги
                if (!(*it)->getBorrowedBooks().empty()) {
                    std::cout << "Невозможно удалить читателя: у него есть не возвращенные книги" << std::endl;
                    return false;
                }
                
                std::cout << "Читатель " << (*it)->getName() << " удален" << std::endl;
                readers.erase(it);
                return true;
            }
        }
        std::cout << "Читатель с ID " << readerId << " не найден" << std::endl;
        return false;
    }
    
    // Выдача книги читателю
    bool borrowBook(int readerId, const std::string& isbn) {
        // Находим читателя
        std::shared_ptr<Reader> reader = nullptr;
        for (const auto& r : readers) {
            if (r->getReaderId() == readerId) {
                reader = r;
                break;
            }
        }
        
        if (!reader) {
            std::cout << "Читатель с ID " << readerId << " не найден" << std::endl;
            return false;
        }
        
        // Находим книгу
        std::shared_ptr<Book> book = nullptr;
        for (const auto& b : books) {
            if (b->getISBN() == isbn) {
                book = b;
                break;
            }
        }
        
        if (!book) {
            std::cout << "Книга с ISBN " << isbn << " не найдена" << std::endl;
            return false;
        }
        
        // Проверяем доступность
        if (!book->isAvailable()) {
            std::cout << "Книга '" << book->getTitle() << "' недоступна" << std::endl;
            return false;
        }
        
        // Выдаем книгу
        if (book->decreaseQuantity()) {
            reader->borrowBook(isbn);
            borrowingRecords[readerId] = isbn; // Для простоты храним только одну запись
            std::cout << "Книга '" << book->getTitle() << "' выдана читателю " 
                      << reader->getName() << std::endl;
            return true;
        }
        
        return false;
    }
    
    // Возврат книги
    bool returnBook(int readerId, const std::string& isbn) {
        // Находим читателя
        std::shared_ptr<Reader> reader = nullptr;
        for (const auto& r : readers) {
            if (r->getReaderId() == readerId) {
                reader = r;
                break;
            }
        }
        
        if (!reader) {
            std::cout << "Читатель с ID " << readerId << " не найден" << std::endl;
            return false;
        }
        
        // Проверяем, брал ли читатель эту книгу
        if (!reader->returnBook(isbn)) {
            std::cout << "Читатель " << reader->getName() 
                      << " не брал книгу с ISBN " << isbn << std::endl;
            return false;
        }
        
        // Находим книгу и увеличиваем количество
        for (const auto& book : books) {
            if (book->getISBN() == isbn) {
                book->increaseQuantity();
                std::cout << "Книга '" << book->getTitle() << "' возвращена читателем " 
                          << reader->getName() << std::endl;
                
                // Удаляем запись о выдаче
                auto it = borrowingRecords.find(readerId);
                if (it != borrowingRecords.end() && it->second == isbn) {
                    borrowingRecords.erase(it);
                }
                return true;
            }
        }
        
        // Если книга не найдена в каталоге (была удалена), добавляем ее обратно
        std::cout << "Книга с ISBN " << isbn << " не найдена в каталоге, создается новая запись" << std::endl;
        // В реальном приложении здесь нужно было бы восстановить информацию о книге
        return false;
    }
    
    // Показать все книги
    void displayAllBooks() const {
        std::cout << "\n=== КАТАЛОГ КНИГ ===" << std::endl;
        if (books.empty()) {
            std::cout << "Библиотека пуста" << std::endl;
        } else {
            for (const auto& book : books) {
                book->displayInfo();
            }
        }
    }
    
    // Показать всех читателей
    void displayAllReaders() const {
        std::cout << "\n=== ЗАРЕГИСТРИРОВАННЫЕ ЧИТАТЕЛИ ===" << std::endl;
        if (readers.empty()) {
            std::cout << "Нет зарегистрированных читателей" << std::endl;
        } else {
            for (const auto& reader : readers) {
                reader->displayInfo();
            }
        }
    }
    
    // Поиск книги по ISBN
    std::shared_ptr<Book> findBookByISBN(const std::string& isbn) const {
        for (const auto& book : books) {
            if (book->getISBN() == isbn) {
                return book;
            }
        }
        return nullptr;
    }
    
    // Поиск читателя по ID
    std::shared_ptr<Reader> findReaderById(int readerId) const {
        for (const auto& reader : readers) {
            if (reader->getReaderId() == readerId) {
                return reader;
            }
        }
        return nullptr;
    }
};

// Функция для тестирования
void testLibrary() {
    std::cout << "=== ТЕСТИРОВАНИЕ БИБЛИОТЕКИ ===" << std::endl;
    
    Library library;
    
    // 1. Добавление книг
    std::cout << "\n1. Добавление книг:" << std::endl;
    library.addBook("Война и мир", "Лев Толстой", "978-5-389-07435-2", 3);
    library.addBook("Преступление и наказание", "Федор Достоевский", "978-5-699-06615-3", 2);
    library.addBook("Мастер и Маргарита", "Михаил Булгаков", "978-5-17-067842-4", 1);
    
    // 2. Регистрация читателей
    std::cout << "\n2. Регистрация читателей:" << std::endl;
    library.registerReader("Иван Иванов", 1001);
    library.registerReader("Петр Петров", 1002);
    library.registerReader("Анна Сидорова", 1003);
    
    // 3. Вывод информации
    library.displayAllBooks();
    library.displayAllReaders();
    
    // 4. Выдача книг
    std::cout << "\n3. Выдача книг:" << std::endl;
    library.borrowBook(1001, "978-5-389-07435-2"); // Иван берет "Войну и мир"
    library.borrowBook(1002, "978-5-699-06615-3"); // Петр берет "Преступление и наказание"
    
    // 5. Попытка взять недоступную книгу
    std::cout << "\n4. Попытка взять недоступную книгу:" << std::endl;
    library.borrowBook(1003, "978-5-699-06615-3"); // Анна пытается взять уже взятую книгу
    
    // 6. Вывод информации после выдачи
    std::cout << "\n5. Состояние после выдачи:" << std::endl;
    library.displayAllBooks();
    library.displayAllReaders();
    
    // 7. Возврат книг
    std::cout << "\n6. Возврат книг:" << std::endl;
    library.returnBook(1001, "978-5-389-07435-2"); // Иван возвращает "Войну и мир"
    
    // 8. Удаление книги
    std::cout << "\n7. Удаление книги:" << std::endl;
    library.removeBook("978-5-17-067842-4", 1); // Удаляем "Мастер и Маргарита"
    
    // 9. Попытка удалить читателя с книгами
    std::cout << "\n8. Попытка удалить читателя с книгами:" << std::endl;
    library.removeReader(1002); // Петр еще не вернул книгу
    
    // 10. Финальное состояние
    std::cout << "\n9. Финальное состояние:" << std::endl;
    library.displayAllBooks();
    library.displayAllReaders();
}

int main() {
    testLibrary();
    return 0;
}
