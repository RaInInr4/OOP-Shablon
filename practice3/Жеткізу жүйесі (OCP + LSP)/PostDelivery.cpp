class PostDelivery : public IDelivery {
public:
    void deliverOrder(const Order& order) override {
        cout << "Post delivered: " << order.getProductName() << endl;
    }
};
