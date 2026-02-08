class SmsNotification : public INotification {
public:
    void sendNotification(const string& message) override {
        cout << "SMS: " << message << endl;
    }
};
