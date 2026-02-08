class INotification {
public:
    virtual void sendNotification(const string& message) = 0;
    virtual ~INotification() {}
};
