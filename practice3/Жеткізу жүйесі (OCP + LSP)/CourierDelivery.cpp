class CourierDelivery : public IDelivery {
public:
    void deliverOrder(const Order& order) override {
        cout << "Courier delivered: " << order.getProductName() << endl;
    }
};
