#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class Logger
{
private:
    static Logger* instance;
    static mutex mtx;

    LogLevel currentLevel;
    string filePath;

    Logger()
    {
        filePath = "log.txt";
        currentLevel = INFO;
    }

public:
    static Logger* GetInstance()
    {
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr)
        {
            instance = new Logger();
        }
        return instance;
    }

    void SetLogLevel(LogLevel level)
    {
        currentLevel = level;
    }

    void Log(string message, LogLevel level)
    {
        if (level < currentLevel)
            return;

        lock_guard<mutex> lock(mtx);

        ofstream file(filePath, ios::app);
        file << "[" << level << "] " << message << endl;
        file.close();
    }
};

Logger* Logger::instance = nullptr;
mutex Logger::mtx;
