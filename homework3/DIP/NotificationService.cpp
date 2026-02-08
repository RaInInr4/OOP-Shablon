class NotificationService {
private:
    INotificationSender* sender;

public:
    NotificationService(INotificationSender* sender) {
        this->sender = sender;
    }

    void sendNotification(const string& message) {
        sender->send(message);
    }
};
