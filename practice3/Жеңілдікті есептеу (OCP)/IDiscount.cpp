class IDiscount {
public:
    virtual double applyDiscount(double amount) = 0;
    virtual ~IDiscount() {}
};
