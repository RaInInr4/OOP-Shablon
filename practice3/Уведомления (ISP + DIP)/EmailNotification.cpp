class EmailNotification : public INotification {
public:
    void sendNotification(const string& message) override {
        cout << "Email: " << message << endl;
    }
};
