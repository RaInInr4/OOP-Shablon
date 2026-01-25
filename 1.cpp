#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1. Базовый класс Vehicle
class Vehicle {
protected:
    string brand;
    string model;
    int year;
    bool engineStarted;
    
public:
    Vehicle(string b, string m, int y) {
        brand = b;
        model = m;
        year = y;
        engineStarted = false;
    }
    
    string startEngine() {
        if (!engineStarted) {
            engineStarted = true;
            return brand + " " + model + ": Двигатель запущен";
        }
        return brand + " " + model + ": Двигатель уже работает";
    }
    
    string stopEngine() {
        if (engineStarted) {
            engineStarted = false;
            return brand + " " + model + ": Двигатель остановлен";
        }
        return brand + " " + model + ": Двигатель уже остановлен";
    }
    
    string getInfo() {
        return brand + " " + model + " (" + to_string(year) + ")";
    }
    
    string getBrand() { return brand; }
    string getModel() { return model; }
    int getYear() { return year; }
    bool isEngineStarted() { return engineStarted; }
};

// 2. Производные классы Car и Motorcycle
class Car : public Vehicle {
private:
    int doors;
    string transmission;
    
public:
    Car(string b, string m, int y, int d, string t) 
        : Vehicle(b, m, y) {
        doors = d;
        transmission = t;
    }
    
    string getInfo() {
        return Vehicle::getInfo() + ", " + to_string(doors) + " дверей, " + transmission;
    }
    
    string getType() {
        return "Автомобиль";
    }
};

class Motorcycle : public Vehicle {
private:
    string bodyType;
    bool hasBox;
    
public:
    Motorcycle(string b, string m, int y, string bt, bool hb) 
        : Vehicle(b, m, y) {
        bodyType = bt;
        hasBox = hb;
    }
    
    string getInfo() {
        string box = hasBox ? "с боксом" : "без бокса";
        return Vehicle::getInfo() + ", " + bodyType + ", " + box;
    }
    
    string getType() {
        return "Мотоцикл";
    }
};

// 3. Классы для композиции - Garage и Fleet
class Garage {
private:
    vector<Vehicle*> vehicles;
    string name;
    
public:
    Garage(string n) {
        name = n;
    }
    
    void addVehicle(Vehicle* v) {
        vehicles.push_back(v);
        cout << v->getInfo() << " добавлен в гараж '" << name << "'" << endl;
    }
    
    void removeVehicle(Vehicle* v) {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i] == v) {
                cout << v->getInfo() << " удален из гаража '" << name << "'" << endl;
                vehicles.erase(vehicles.begin() + i);
                return;
            }
        }
        cout << "Транспорт не найден в гараже '" << name << "'" << endl;
    }
    
    void showVehicles() {
        cout << "=== ГАРАЖ '" << name << "' ===" << endl;
        if (vehicles.empty()) {
            cout << "Гараж пуст" << endl;
            return;
        }
        
        for (int i = 0; i < vehicles.size(); i++) {
            Car* car = dynamic_cast<Car*>(vehicles[i]);
            Motorcycle* bike = dynamic_cast<Motorcycle*>(vehicles[i]);
            
            if (car) {
                cout << i+1 << ". " << car->getType() << ": " << car->getInfo() << endl;
            } else if (bike) {
                cout << i+1 << ". " << bike->getType() << ": " << bike->getInfo() << endl;
            } else {
                cout << i+1 << ". Транспорт: " << vehicles[i]->getInfo() << endl;
            }
        }
    }
    
    string getName() {
        return name;
    }
    
    vector<Vehicle*> getVehicles() {
        return vehicles;
    }
};

class Fleet {
private:
    vector<Garage*> garages;
    string name;
    
public:
    Fleet(string n) {
        name = n;
    }
    
    void addGarage(Garage* g) {
        garages.push_back(g);
        cout << "Гараж '" << g->getName() << "' добавлен в автопарк '" << name << "'" << endl;
    }
    
    void removeGarage(Garage* g) {
        for (int i = 0; i < garages.size(); i++) {
            if (garages[i] == g) {
                cout << "Гараж '" << g->getName() << "' удален из автопарка '" << name << "'" << endl;
                garages.erase(garages.begin() + i);
                return;
            }
        }
        cout << "Гараж не найден в автопарке '" << name << "'" << endl;
    }
    
    void findVehicle(string brand) {
        cout << "=== ПОИСК транспорта марки " << brand << " ===" << endl;
        bool found = false;
        
        for (Garage* garage : garages) {
            vector<Vehicle*> vehicles = garage->getVehicles();
            
            for (Vehicle* vehicle : vehicles) {
                if (vehicle->getBrand() == brand) {
                    cout << "Найден в гараже '" << garage->getName() << "': ";
                    cout << vehicle->getInfo() << endl;
                    found = true;
                }
            }
        }
        
        if (!found) {
            cout << "Транспорт марки " << brand << " не найден" << endl;
        }
    }
    
    void showFleet() {
        cout << "=== АВТОПАРК '" << name << "' ===" << endl;
        if (garages.empty()) {
            cout << "Автопарк пуст" << endl;
            return;
        }
        
        for (Garage* garage : garages) {
            cout << "Гараж: " << garage->getName() << endl;
            garage->showVehicles();
            cout << endl;
        }
    }
};

// 4. Тестирование
int main() {
    cout << "=== ТЕСТИРОВАНИЕ ПРИЛОЖЕНИЯ ===" << endl;
    
    // Создаем транспортные средства
    cout << "\n1. СОЗДАЕМ ТРАНСПОРТ:" << endl;
    
    Car car1("Toyota", "Camry", 2022, 4, "автоматическая");
    Car car2("Honda", "Civic", 2023, 4, "механическая");
    Car car3("BMW", "X5", 2021, 5, "автоматическая");
    
    Motorcycle bike1("Harley-Davidson", "Sportster", 2020, "круизер", true);
    Motorcycle bike2("Yamaha", "YZF-R3", 2023, "спортивный", false);
    
    cout << "Создано 3 автомобиля и 2 мотоцикла" << endl;
    
    // Создаем гаражи и добавляем транспорт
    cout << "\n2. СОЗДАЕМ И ЗАПОЛНЯЕМ ГАРАЖИ:" << endl;
    
    Garage garage1("Центральный");
    Garage garage2("Северный");
    
    garage1.addVehicle(&car1);
    garage1.addVehicle(&car2);
    garage1.addVehicle(&bike1);
    
    garage2.addVehicle(&car3);
    garage2.addVehicle(&bike2);
    
    cout << "\n3. ПОКАЗЫВАЕМ СОДЕРЖИМОЕ ГАРАЖЕЙ:" << endl;
    garage1.showVehicles();
    cout << endl;
    garage2.showVehicles();
    
    // Тестируем двигатели (полиморфизм)
    cout << "\n4. ТЕСТИРУЕМ ДВИГАТЕЛИ (полиморфизм):" << endl;
    
    Vehicle* vehicles[] = {&car1, &bike1, &car3};
    
    for (int i = 0; i < 3; i++) {
        cout << vehicles[i]->startEngine() << endl;
    }
    
    cout << "\nПовторный запуск:" << endl;
    cout << car1.startEngine() << endl;
    
    cout << "\nОстановка двигателей:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << vehicles[i]->stopEngine() << endl;
    }
    
    // Создаем автопарк
    cout << "\n5. СОЗДАЕМ АВТОПАРК:" << endl;
    
    Fleet fleet("Основной");
    fleet.addGarage(&garage1);
    fleet.addGarage(&garage2);
    
    cout << "\n6. ПОКАЗЫВАЕМ ВЕСЬ АВТОПАРК:" << endl;
    fleet.showFleet();
    
    // Тестируем поиск
    cout << "\n7. ТЕСТИРУЕМ ПОИСК:" << endl;
    fleet.findVehicle("Honda");
    fleet.findVehicle("Toyota");
    fleet.findVehicle("Audi"); // Несуществующий
    
    // Тестируем удаление
    cout << "\n8. ТЕСТИРУЕМ УДАЛЕНИЕ:" << endl;
    garage1.removeVehicle(&car2);
    cout << "\nПосле удаления Honda Civic:" << endl;
    garage1.showVehicles();
    
    fleet.removeGarage(&garage2);
    cout << "\nПосле удаления гаража:" << endl;
    fleet.showFleet();
    
    cout << "\nтест завершен " << endl;
    
    return 0;
}