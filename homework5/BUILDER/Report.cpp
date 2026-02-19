class Report
{
public:
    string header;
    string content;
    string footer;

    void Show()
    {
        cout << header << endl;
        cout << content << endl;
        cout << footer << endl;
    }
};
