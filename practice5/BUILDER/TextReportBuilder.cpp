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
        report->header = header;
    }

    void SetContent(string content)
    {
        report->content = content;
    }

    void SetFooter(string footer)
    {
        report->footer = footer;
    }

    void AddSection(string name, string content)
    {
        report->sections.push_back(name + ": " + content);
    }

    void SetStyle(ReportStyle style)
    {
        // Text report style ignored for simplicity
    }

    Report* GetReport()
    {
        return report;
    }
};
