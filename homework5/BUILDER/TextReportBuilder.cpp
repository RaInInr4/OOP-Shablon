class TextReportBuilder : public IReportBuilder
{
private:
    Report* report;

public:
    TextReportBuilder()
    {
        report = new Report();
    }

    void SetHeader(string header)
    {
        report->header = "TEXT HEADER: " + header;
    }

    void SetContent(string content)
    {
        report->content = content;
    }

    void SetFooter(string footer)
    {
        report->footer = "TEXT FOOTER: " + footer;
    }

    Report* GetReport()
    {
        return report;
    }
};
