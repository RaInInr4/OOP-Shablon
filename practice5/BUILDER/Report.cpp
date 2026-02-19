#include <vector>

class Report
{
public:
    string header;
    string content;
    string footer;
    vector<string> sections;

    void Export()
    {
        cout << header << endl;
        cout << content << endl;

        for (int i = 0; i < sections.size(); i++)
        {
            cout << sections[i] << endl;
        }

        cout << footer << endl;
    }
};
