void ThreadTest(int id)
{
    ConfigurationManager* config = ConfigurationManager::GetInstance();
    config->SetSetting("Thread" + to_string(id), "Active");
}

int main()
{
    thread t1(ThreadTest, 1);
    thread t2(ThreadTest, 2);

    t1.join();
    t2.join();

    ConfigurationManager* config = ConfigurationManager::GetInstance();

    config->SaveToFile("config.txt");

    cout << "Singleton works successfully!" << endl;

    return 0;
}
