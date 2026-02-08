class IDelivery {
public:
    virtual void deliverOrder(const Order& order) = 0;
    virtual ~IDelivery() {}
};
