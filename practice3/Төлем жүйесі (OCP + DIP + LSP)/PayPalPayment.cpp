class PayPalPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << "Paid " << amount << " via PayPal" << endl;
    }
};
