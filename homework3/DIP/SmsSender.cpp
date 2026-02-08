class SmsSender : public INotificationSender {
public:
    void send(const string& message) override {
        cout << "SMS sent: " << message << endl;
    }
};
