class PercentageDiscount : public IDiscount {
public:
    double applyDiscount(double amount) override {
        return amount * 0.9; // 10% жеңілдік
    }
};
