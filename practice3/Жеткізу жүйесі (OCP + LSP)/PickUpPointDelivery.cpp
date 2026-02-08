class PickUpPointDelivery : public IDelivery {
public:
    void deliverOrder(const Order& order) override {
        cout << "Picked up from delivery point: "
             << order.getProductName() << endl;
    }
};
