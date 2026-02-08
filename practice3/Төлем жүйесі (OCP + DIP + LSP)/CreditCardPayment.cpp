class CreditCardPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << "Paid " << amount << " by Credit Card" << endl;
    }
};
