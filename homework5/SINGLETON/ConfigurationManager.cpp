#include <iostream>
#include <map>
#include <string>
#include <mutex>
#include <fstream>
#include <thread>

using namespace std;

class ConfigurationManager
{
private:
    static ConfigurationManager* instance;
    static mutex mtx;

    map<string, string> settings;

    // Приватный конструктор
    ConfigurationManager() {}

public:
    // Потокобезопасный Singleton
    static ConfigurationManager* GetInstance()
    {
        lock_guard<mutex> lock(mtx);

        if (instance == nullptr)
        {
            instance = new ConfigurationManager();
        }
        return instance;
    }

    void SetSetting(string key, string value)
    {
        settings[key] = value;
    }

    string GetSetting(string key)
    {
        if (settings.find(key) != settings.end())
            return settings[key];

        throw runtime_error("Setting not found!");
    }

    void SaveToFile(string filename)
    {
        ofstream file(filename);

        for (auto pair : settings)
        {
            file << pair.first << "=" << pair.second << endl;
        }

        file.close();
    }

    void LoadFromFile(string filename)
    {
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            int pos = line.find("=");
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            settings[key] = value;
        }

        file.close();
    }
};

ConfigurationManager* ConfigurationManager::instance = nullptr;
mutex ConfigurationManager::mtx;
