class LogReader
{
private:
    string filePath;

public:
    LogReader(string path) : filePath(path) {}

    void Read(LogLevel level)
    {
        ifstream file(filePath);
        string line;

        while (getline(file, line))
        {
            if (line.find(to_string(level)) != string::npos)
            {
                cout << line << endl;
            }
        }

        file.close();
    }
};
