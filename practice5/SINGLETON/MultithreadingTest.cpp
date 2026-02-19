void ThreadFunction(int id)
{
    Logger* logger = Logger::GetInstance();

    logger->Log("Thread " + to_string(id) + " INFO", INFO);
    logger->Log("Thread " + to_string(id) + " WARNING", WARNING);
    logger->Log("Thread " + to_string(id) + " ERROR", ERROR);
}

int main()
{
    Logger* logger = Logger::GetInstance();
    logger->SetLogLevel(INFO);

    vector<thread> threads;

    for (int i = 1; i <= 3; i++)
    {
        threads.push_back(thread(ThreadFunction, i));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    LogReader reader("log.txt");
    reader.Read(ERROR);

    return 0;
}
