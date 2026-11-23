#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Observer {
public:
    virtual void notify(const string& message) = 0;
    virtual ~Observer() {}
};

class EmailNotification : public Observer {
private:
    string email;
public:
    explicit EmailNotification(string e) : email(e) {}
    void notify(const string& message) override {
        cout << "Email notification to " << email << ": " << message << '\n';
    }
};

class SMSNotification : public Observer {
private:
    string phone;
public:
    explicit SMSNotification(string p) : phone(p) {}
    void notify(const string& message) override {
        cout << "SMS notification to " << phone << ": " << message << '\n';
    }
};

class NotificationFactory {
public:
    static shared_ptr<Observer> createNotification(
        const string& type, const string& receiver) {
        if (type == "EMAIL")
            return make_shared<EmailNotification>(receiver);
        if (type == "SMS")
            return make_shared<SMSNotification>(receiver);
        return nullptr;
    }
};

class EventManager {
private:
    vector<shared_ptr<Observer>> observers;
    EventManager() {}

public:
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer) {
        if (observer) observers.push_back(observer);
    }

    void triggerEvent(const string& message) {
        cout << "\nEvent: " << message << '\n';
        for (const auto& observer : observers)
            observer->notify(message);
    }
};

int main() {
    EventManager& manager = EventManager::getInstance();
    int count;
    cout << "How many notification recipients? ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        string type, receiver;
        cout << "\nRecipient " << i + 1 << " type (EMAIL/SMS): ";
        cin >> type;
        cout << "Enter email address or phone number: ";
        cin >> receiver;

        for (char& c : type) c = static_cast<char>(toupper(c));
        auto observer = NotificationFactory::createNotification(type, receiver);

        if (observer)
            manager.subscribe(observer);
        else
            cout << "Unknown notification type. Recipient skipped.\n";
    }

    cin.ignore();
    string message;
    cout << "\nEnter event message: ";
    getline(cin, message);

    manager.triggerEvent(message);
    return 0;
}
