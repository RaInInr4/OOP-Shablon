#include <iostream>
#include <string>

using namespace std;

/* ------------ DECORATOR PATTERN (CAFE) ------------ */

class Beverage {
public:
    virtual string Description() {
        return "Unknown beverage";
    }

    virtual double Cost() = 0;
};

// Базалық сусындар
class Espresso : public Beverage {
public:
    string Description() {
        return "Espresso";
    }

    double Cost() {
        return 2.0;
    }
};

class Tea : public Beverage {
public:
    string Description() {
        return "Tea";
    }

    double Cost() {
        return 1.5;
    }
};

class Latte : public Beverage {
public:
    string Description() {
        return "Latte";
    }

    double Cost() {
        return 3.0;
    }
};

// Абстракт декоратор
class BeverageDecorator : public Beverage {
protected:
    Beverage* beverage;

public:
    BeverageDecorator(Beverage* b) {
        beverage = b;
    }
};

// Milk
class Milk : public BeverageDecorator {
public:
    Milk(Beverage* b) : BeverageDecorator(b) {}

    string Description() {
        return beverage->Description() + " + Milk";
    }

    double Cost() {
        return beverage->Cost() + 0.5;
    }
};

// Sugar
class Sugar : public BeverageDecorator {
public:
    Sugar(Beverage* b) : BeverageDecorator(b) {}

    string Description() {
        return beverage->Description() + " + Sugar";
    }

    double Cost() {
        return beverage->Cost() + 0.2;
    }
};

// Whipped Cream
class WhippedCream : public BeverageDecorator {
public:
    WhippedCream(Beverage* b) : BeverageDecorator(b) {}

    string Description() {
        return beverage->Description() + " + Whipped Cream";
    }

    double Cost() {
        return beverage->Cost() + 0.7;
    }
};


/* ------------ ADAPTER PATTERN (PAYMENT) ------------ */

// Негізгі интерфейс
class IPaymentProcessor {
public:
    virtual void ProcessPayment(double amount) = 0;
};

// PayPal
class PayPalPaymentProcessor : public IPaymentProcessor {
public:
    void ProcessPayment(double amount) {
        cout << "Payment via PayPal: $" << amount << endl;
    }
};

// Сыртқы Stripe сервисі
class StripePaymentService {
public:
    void MakeTransaction(double totalAmount) {
        cout << "Stripe transaction: $" << totalAmount << endl;
    }
};

// Adapter
class StripePaymentAdapter : public IPaymentProcessor {

private:
    StripePaymentService stripe;

public:
    void ProcessPayment(double amount) {
        stripe.MakeTransaction(amount);
    }
};


/* ------------ MAIN ------------ */

int main() {

    cout << "===== DECORATOR (Cafe) =====" << endl;

    Beverage* drink = new Espresso();

    drink = new Milk(drink);
    drink = new Sugar(drink);
    drink = new WhippedCream(drink);

    cout << "Drink: " << drink->Description() << endl;
    cout << "Total cost: $" << drink->Cost() << endl;


    cout << "\n===== ADAPTER (Payment) =====" << endl;

    IPaymentProcessor* payment;

    payment = new PayPalPaymentProcessor();
    payment->ProcessPayment(15.0);

    payment = new StripePaymentAdapter();
    payment->ProcessPayment(20.0);

    return 0;
}