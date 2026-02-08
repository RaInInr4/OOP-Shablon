#include <iostream>
#include <string>
using namespace std;

class Order {
private:
    string productName;
    int quantity;
    double price;

public:
    Order(string name, int qty, double pr)
        : productName(name), quantity(qty), price(pr) {}

    double getTotalPrice() const {
        return quantity * price;
    }

    string getProductName() const {
        return productName;
    }
};
