class INotificationSender {
public:
    virtual void send(const string& message) = 0;
    virtual ~INotificationSender() {}
};
