// Расчет стоимости
class OrderPriceCalculator {
public:
    double calculateTotalPrice(const Order& order) {
        return order.quantity * order.price * 0.9; // скидка 10%
    }
};
