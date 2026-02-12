#include <iostream>
#include <string>

using namespace std;

// =========================
// 1. Интерфейс IVehicle
// =========================
class IVehicle {
public:
    virtual void Drive() = 0;
    virtual void Refuel() = 0;
    virtual ~IVehicle() {}
};

// =========================
// 2. Конкретные транспортные средства
// =========================

// ---- Car ----
class Car : public IVehicle {
private:
    string brand;
    string model;
    string fuelType;

public:
    Car(string b, string m, string f) {
        brand = b;
        model = m;
        fuelType = f;
    }

    void Drive() {
        cout << "Car " << brand << " " << model << " is driving." << endl;
    }

    void Refuel() {
        cout << "Car refueling with " << fuelType << "." << endl;
    }
};

// ---- Motorcycle ----
class Motorcycle : public IVehicle {
private:
    string type;
    int engineVolume;

public:
    Motorcycle(string t, int e) {
        type = t;
        engineVolume = e;
    }

    void Drive() {
        cout << type << " motorcycle with engine "
             << engineVolume << "cc is driving." << endl;
    }

    void Refuel() {
        cout << "Motorcycle refueling." << endl;
    }
};

// ---- Truck ----
class Truck : public IVehicle {
private:
    int loadCapacity;
    int axles;

public:
    Truck(int l, int a) {
        loadCapacity = l;
        axles = a;
    }

    void Drive() {
        cout << "Truck with load capacity "
             << loadCapacity << " tons is driving." << endl;
    }

    void Refuel() {
        cout << "Truck refueling diesel." << endl;
    }
};

// ---- Bus (новый тип) ----
class Bus : public IVehicle {
private:
    int passengerCapacity;
    string route;

public:
    Bus(int p, string r) {
        passengerCapacity = p;
        route = r;
    }

    void Drive() {
        cout << "Bus on route " << route
             << " with capacity " << passengerCapacity
             << " passengers is driving." << endl;
    }

    void Refuel() {
        cout << "Bus refueling." << endl;
    }
};

// =========================
// 3. Абстрактная фабрика
// =========================
class VehicleFactory {
public:
    virtual IVehicle* CreateVehicle() = 0;
    virtual ~VehicleFactory() {}
};

// =========================
// 4. Конкретные фабрики
// =========================

// ---- CarFactory ----
class CarFactory : public VehicleFactory {
private:
    string brand;
    string model;
    string fuelType;

public:
    CarFactory(string b, string m, string f) {
        brand = b;
        model = m;
        fuelType = f;
    }

    IVehicle* CreateVehicle() {
        return new Car(brand, model, fuelType);
    }
};

// ---- MotorcycleFactory ----
class MotorcycleFactory : public VehicleFactory {
private:
    string type;
    int engineVolume;

public:
    MotorcycleFactory(string t, int e) {
        type = t;
        engineVolume = e;
    }

    IVehicle* CreateVehicle() {
        return new Motorcycle(type, engineVolume);
    }
};

// ---- TruckFactory ----
class TruckFactory : public VehicleFactory {
private:
    int loadCapacity;
    int axles;

public:
    TruckFactory(int l, int a) {
        loadCapacity = l;
        axles = a;
    }

    IVehicle* CreateVehicle() {
        return new Truck(loadCapacity, axles);
    }
};

// ---- BusFactory ----
class BusFactory : public VehicleFactory {
private:
    int passengerCapacity;
    string route;

public:
    BusFactory(int p, string r) {
        passengerCapacity = p;
        route = r;
    }

    IVehicle* CreateVehicle() {
        return new Bus(passengerCapacity, route);
    }
};

// =========================
// 5. Main — динамический ввод
// =========================

int main() {
    int choice;
    VehicleFactory* factory = NULL;

    cout << "Select vehicle type:" << endl;
    cout << "1 - Car" << endl;
    cout << "2 - Motorcycle" << endl;
    cout << "3 - Truck" << endl;
    cout << "4 - Bus" << endl;
    cout << "Enter number: ";
    cin >> choice;

    if (choice == 1) {
        string brand, model, fuel;
        cout << "Enter brand: ";
        cin >> brand;
        cout << "Enter model: ";
        cin >> model;
        cout << "Enter fuel type: ";
        cin >> fuel;

        factory = new CarFactory(brand, model, fuel);
    }
    else if (choice == 2) {
        string type;
        int engine;
        cout << "Enter motorcycle type: ";
        cin >> type;
        cout << "Enter engine volume: ";
        cin >> engine;

        factory = new MotorcycleFactory(type, engine);
    }
    else if (choice == 3) {
        int load, axles;
        cout << "Enter load capacity (tons): ";
        cin >> load;
        cout << "Enter number of axles: ";
        cin >> axles;

        factory = new TruckFactory(load, axles);
    }
    else if (choice == 4) {
        int capacity;
        string route;
        cout << "Enter passenger capacity: ";
        cin >> capacity;
        cout << "Enter route name: ";
        cin >> route;

        factory = new BusFactory(capacity, route);
    }
    else {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    IVehicle* vehicle = factory->CreateVehicle();

    vehicle->Drive();
    vehicle->Refuel();

    delete vehicle;
    delete factory;

    return 0;
}
