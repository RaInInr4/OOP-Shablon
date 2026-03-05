#include <iostream>
#include <string>
using namespace std;

/* =========================
   COMMAND PATTERN
   ========================= */

class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
public:
    void on() { cout << "Light ON\n"; }
    void off() { cout << "Light OFF\n"; }
};

class LightOnCommand : public ICommand {
    Light* light;
public:
    LightOnCommand(Light* l) {
        light = l;
    }

    void execute() {
        light->on();
    }

    void undo() {
        light->off();
    }
};

class RemoteControl {
    ICommand* command;
public:
    void setCommand(ICommand* c) {
        command = c;
    }

    void pressButton() {
        command->execute();
    }

    void pressUndo() {
        command->undo();
    }
};

/* =========================
   TEMPLATE METHOD PATTERN
   ========================= */

class Beverage {
public:
    void prepare() {
        boilWater();
        brew();
        pour();
        addCondiments();
    }

    void boilWater() {
        cout << "Boiling water\n";
    }

    void pour() {
        cout << "Pouring into cup\n";
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;
};

class Tea : public Beverage {
public:
    void brew() {
        cout << "Steeping tea\n";
    }

    void addCondiments() {
        cout << "Adding lemon\n";
    }
};

class Coffee : public Beverage {
public:
    void brew() {
        cout << "Brewing coffee\n";
    }

    void addCondiments() {
        cout << "Adding sugar and milk\n";
    }
};

/* =========================
   MEDIATOR PATTERN
   ========================= */

class User;

class IMediator {
public:
    virtual void sendMessage(string msg, User* user) = 0;
};

class User {
protected:
    IMediator* mediator;
    string name;

public:
    User(IMediator* m, string n) {
        mediator = m;
        name = n;
    }

    void send(string msg) {
        mediator->sendMessage(msg, this);
    }

    void receive(string msg) {
        cout << name << " received: " << msg << endl;
    }

    string getName() {
        return name;
    }
};

class ChatRoom : public IMediator {
    User* users[10];
    int count = 0;

public:
    void addUser(User* user) {
        users[count] = user;
        count++;
    }

    void sendMessage(string msg, User* sender) {
        for(int i = 0; i < count; i++) {
            if(users[i] != sender) {
                users[i]->receive(sender->getName() + ": " + msg);
            }
        }
    }
};

/* =========================
   MAIN (DEMO)
   ========================= */

int main() {

    cout << "=== COMMAND PATTERN ===\n";

    Light light;
    LightOnCommand lightOn(&light);
    RemoteControl remote;

    remote.setCommand(&lightOn);
    remote.pressButton();
    remote.pressUndo();


    cout << "\n=== TEMPLATE METHOD PATTERN ===\n";

    Tea tea;
    Coffee coffee;

    cout << "Tea:\n";
    tea.prepare();

    cout << "\nCoffee:\n";
    coffee.prepare();


    cout << "\n=== MEDIATOR PATTERN ===\n";

    ChatRoom chat;

    User u1(&chat,"Ali");
    User u2(&chat,"Dana");
    User u3(&chat,"Arman");

    chat.addUser(&u1);
    chat.addUser(&u2);
    chat.addUser(&u3);

    u1.send("Salem!");

    return 0;
}