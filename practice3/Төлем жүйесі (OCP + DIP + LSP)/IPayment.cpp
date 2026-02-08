class IPayment {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~IPayment() {}
};
