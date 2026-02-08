class EmailSender : public INotificationSender {
public:
    void send(const string& message) override {
        cout << "Email sent: " << message << endl;
    }
};
