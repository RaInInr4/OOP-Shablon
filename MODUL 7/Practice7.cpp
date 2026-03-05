#include <iostream>
#include <string>
using namespace std;

/* ======================
   COMMAND PATTERN
   ======================*/

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

class TV {
public:
    void on() { cout << "TV ON\n"; }
    void off() { cout << "TV OFF\n"; }
};

class LightOnCommand : public ICommand {
    Light* light;
public:
    LightOnCommand(Light* l) { light = l; }

    void execute() { light->on(); }
    void undo() { light->off(); }
};

class TVOnCommand : public ICommand {
    TV* tv;
public:
    TVOnCommand(TV* t) { tv = t; }

    void execute() { tv->on(); }
    void undo() { tv->off(); }
};

class RemoteControl {
    ICommand* lastCommand;
public:
    void press(ICommand* command) {
        command->execute();
        lastCommand = command;
    }

    void undo() {
        if(lastCommand)
            lastCommand->undo();
        else
            cout << "No command to undo\n";
    }
};

/* ======================
   TEMPLATE METHOD
   ======================*/

class ReportGenerator {
public:
    void generate() {
        collectData();
        formatReport();
        saveReport();
    }

    void collectData() {
        cout << "Collecting data\n";
    }

    virtual void formatReport() = 0;
    virtual void saveReport() = 0;
};

class PdfReport : public ReportGenerator {
public:
    void formatReport() {
        cout << "Formatting PDF report\n";
    }

    void saveReport() {
        cout << "Saving PDF file\n";
    }
};

class ExcelReport : public ReportGenerator {
public:
    void formatReport() {
        cout << "Formatting Excel report\n";
    }

    void saveReport() {
        cout << "Saving Excel file\n";
    }
};

class HtmlReport : public ReportGenerator {
public:
    void formatReport() {
        cout << "Formatting HTML report\n";
    }

    void saveReport() {
        cout << "Saving HTML file\n";
    }
};

/* ======================
   MEDIATOR PATTERN
   ======================*/

class User;

class IMediator {
public:
    virtual void sendMessage(string msg, User* sender) = 0;
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

class ChatMediator : public IMediator {
    User* users[10];
    int count = 0;

public:
    void addUser(User* user) {
        users[count++] = user;
        cout << user->getName() << " joined chat\n";
    }

    void sendMessage(string msg, User* sender) {
        for(int i=0;i<count;i++) {
            if(users[i] != sender)
                users[i]->receive(sender->getName() + ": " + msg);
        }
    }
};

/* ======================
   MAIN
   ======================*/

int main() {

    cout << "=== COMMAND ===\n";

    Light light;
    TV tv;

    LightOnCommand lightCmd(&light);
    TVOnCommand tvCmd(&tv);

    RemoteControl remote;

    remote.press(&lightCmd);
    remote.undo();

    remote.press(&tvCmd);


    cout << "\n=== TEMPLATE METHOD ===\n";

    PdfReport pdf;
    ExcelReport excel;
    HtmlReport html;

    pdf.generate();
    cout << endl;
    excel.generate();
    cout << endl;
    html.generate();


    cout << "\n=== MEDIATOR ===\n";

    ChatMediator chat;

    User u1(&chat,"Ali");
    User u2(&chat,"Dana");
    User u3(&chat,"Arman");

    chat.addUser(&u1);
    chat.addUser(&u2);
    chat.addUser(&u3);

    u1.send("Hello everyone");

    return 0;
}