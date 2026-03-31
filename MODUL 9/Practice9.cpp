#include <iostream>
#include <string>
using namespace std;

// ----------- FACADE PATTERN (Hotel System) -----------

// Room Booking
class RoomBookingSystem {
public:
    void bookRoom(string name) {
        cout << "Room booked for " << name << endl;
    }

    void cancelBooking(string name) {
        cout << "Booking cancelled for " << name << endl;
    }
};

// Restaurant
class RestaurantSystem {
public:
    void reserveTable(string name) {
        cout << "Table reserved for " << name << endl;
    }

    void orderFood(string food) {
        cout << "Food ordered: " << food << endl;
    }
};

// Event Management
class EventManagementSystem {
public:
    void bookHall(string eventName) {
        cout << "Hall booked for event: " << eventName << endl;
    }

    void orderEquipment() {
        cout << "Equipment ordered for event" << endl;
    }
};

// Cleaning Service
class CleaningService {
public:
    void scheduleCleaning(int room) {
        cout << "Cleaning scheduled for room " << room << endl;
    }

    void cleanRoom(int room) {
        cout << "Room " << room << " cleaned" << endl;
    }
};

// Facade
class HotelFacade {

private:
    RoomBookingSystem roomSystem;
    RestaurantSystem restaurant;
    EventManagementSystem events;
    CleaningService cleaning;

public:

    void bookRoomWithServices(string name) {
        cout << "\n--- Room Booking ---\n";
        roomSystem.bookRoom(name);
        restaurant.orderFood("Dinner");
        cleaning.scheduleCleaning(101);
    }

    void organizeEvent(string eventName) {
        cout << "\n--- Event Organization ---\n";
        events.bookHall(eventName);
        events.orderEquipment();
        roomSystem.bookRoom("Event Guests");
    }

    void reserveRestaurantWithTaxi(string name) {
        cout << "\n--- Restaurant Reservation ---\n";
        restaurant.reserveTable(name);
        cout << "Taxi ordered for " << name << endl;
    }

    void cancelRoom(string name) {
        roomSystem.cancelBooking(name);
    }
};

// ----------- COMPOSITE PATTERN (Organization Structure) -----------

class OrganizationComponent {
public:
    virtual void display(int level = 0) = 0;
    virtual int getSalary() = 0;
    virtual int getEmployeeCount() = 0;
    virtual ~OrganizationComponent() {}
};

// Employee
class Employee : public OrganizationComponent {

private:
    string name;
    string position;
    int salary;

public:
    Employee(string n, string p, int s) {
        name = n;
        position = p;
        salary = s;
    }

    void display(int level = 0) {
        for(int i=0;i<level;i++) cout << "-";
        cout << name << " (" << position << ") salary: " << salary << endl;
    }

    int getSalary() {
        return salary;
    }

    int getEmployeeCount() {
        return 1;
    }
};

// Department
class Department : public OrganizationComponent {

private:
    string name;
    OrganizationComponent* items[10];
    int count;

public:
    Department(string n) {
        name = n;
        count = 0;
    }

    void add(OrganizationComponent* comp) {
        if(count < 10) {
            items[count] = comp;
            count++;
        }
    }

    void display(int level = 0) {
        for(int i=0;i<level;i++) cout << "-";
        cout << "Department: " << name << endl;

        for(int i=0;i<count;i++) {
            items[i]->display(level + 2);
        }
    }

    int getSalary() {
        int total = 0;

        for(int i=0;i<count;i++) {
            total += items[i]->getSalary();
        }

        return total;
    }

    int getEmployeeCount() {
        int total = 0;

        for(int i=0;i<count;i++) {
            total += items[i]->getEmployeeCount();
        }

        return total;
    }
};

// ----------- MAIN -----------

int main() {

    // Facade қолдану
    HotelFacade hotel;

    hotel.bookRoomWithServices("Ali");
    hotel.organizeEvent("Business Conference");
    hotel.reserveRestaurantWithTaxi("Dana");

    cout << "\n========================\n";

    // Composite қолдану
    Department* company = new Department("Company");

    Employee* e1 = new Employee("Arman","Manager",5000);
    Employee* e2 = new Employee("Dana","Developer",4000);

    Department* itDept = new Department("IT Department");
    Employee* e3 = new Employee("Aruzhan","Programmer",3500);

    itDept->add(e3);

    company->add(e1);
    company->add(e2);
    company->add(itDept);

    company->display();

    cout << "\nTotal salary budget: " << company->getSalary() << endl;
    cout << "Total employees: " << company->getEmployeeCount() << endl;

    return 0;
}