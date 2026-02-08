int main() {
    Order order("Laptop", 1, 500000);

    IPayment* payment = new CreditCardPayment();
    IDelivery* delivery = new CourierDelivery();
    INotification* notification = new EmailNotification();
    IDiscount* discount = new PercentageDiscount();

    DiscountCalculator calculator;
    double finalPrice = calculator.calculate(order.getTotalPrice(), discount);

    payment->processPayment(finalPrice);
    delivery->deliverOrder(order);
    notification->sendNotification("Your order has been processed!");

    delete payment;
    delete delivery;
    delete notification;
    delete discount;

    return 0;
}
