#include <iostream>
#include <string>
using namespace std;

// ----------- Facade Pattern -----------

// TV
class TV {
public:
    void on() { cout << "TV ON\n"; }
    void off() { cout << "TV OFF\n"; }
    void setChannel(int ch) { cout << "TV channel: " << ch << endl; }
};

// Audio System
class AudioSystem {
public:
    void on() { cout << "Audio ON\n"; }
    void off() { cout << "Audio OFF\n"; }
    void setVolume(int v) { cout << "Volume: " << v << endl; }
};

// DVD Player
class DVDPlayer {
public:
    void play() { cout << "DVD playing\n"; }
    void pause() { cout << "DVD paused\n"; }
    void stop() { cout << "DVD stopped\n"; }
};

// Game Console
class GameConsole {
public:
    void on() { cout << "Console ON\n"; }
    void startGame() { cout << "Game started\n"; }
};

// Facade
class HomeTheaterFacade {
private:
    TV tv;
    AudioSystem audio;
    DVDPlayer dvd;
    GameConsole console;

public:
    void watchMovie() {
        cout << "\nStart Movie\n";
        tv.on();
        audio.on();
        audio.setVolume(10);
        dvd.play();
    }

    void playGame() {
        cout << "\nStart Game\n";
        tv.on();
        console.on();
        console.startGame();
    }

    void systemOff() {
        cout << "\nSystem OFF\n";
        dvd.stop();
        audio.off();
        tv.off();
    }
};

// ----------- Composite Pattern -----------

class FileSystemComponent {
public:
    virtual void display(int level = 0) = 0;
    virtual int getSize() = 0;
    virtual ~FileSystemComponent() {}
};

// File
class File : public FileSystemComponent {
private:
    string name;
    int size;

public:
    File(string n, int s) {
        name = n;
        size = s;
    }

    void display(int level = 0) {
        for(int i=0;i<level;i++) cout << "-";
        cout << "File: " << name << " size: " << size << endl;
    }

    int getSize() {
        return size;
    }
};

// Directory
class Directory : public FileSystemComponent {
private:
    string name;
    FileSystemComponent* items[10];
    int count;

public:
    Directory(string n) {
        name = n;
        count = 0;
    }

    void add(FileSystemComponent* comp) {
        if(count < 10) {
            items[count] = comp;
            count++;
        }
    }

    void display(int level = 0) {
        for(int i=0;i<level;i++) cout << "-";
        cout << "Directory: " << name << endl;

        for(int i=0;i<count;i++) {
            items[i]->display(level + 2);
        }
    }

    int getSize() {
        int total = 0;
        for(int i=0;i<count;i++) {
            total += items[i]->getSize();
        }
        return total;
    }
};

// ----------- Main -----------

int main() {

    // Facade қолдану
    HomeTheaterFacade home;

    home.watchMovie();
    home.playGame();
    home.systemOff();

    cout << "\n--- File System ---\n";

    // Composite қолдану
    Directory* root = new Directory("Root");

    File* f1 = new File("file1.txt", 10);
    File* f2 = new File("file2.txt", 20);

    Directory* docs = new Directory("Documents");
    File* f3 = new File("doc1.txt", 30);

    docs->add(f3);

    root->add(f1);
    root->add(f2);
    root->add(docs);

    root->display();

    cout << "Total size: " << root->getSize() << endl;

    return 0;
}