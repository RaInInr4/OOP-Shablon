class DiscountCalculator {
public:
    double calculate(double amount, IDiscount* discount) {
        return discount->applyDiscount(amount);
    }
};
