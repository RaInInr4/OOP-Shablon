class HtmlReportBuilder : public IReportBuilder
{
private:
    Report* report;

public:
    HtmlReportBuilder()
    {
        report = new Report();
    }

    void SetHeader(string header)
    {
        report->header = "<h1>" + header + "</h1>";
    }

    void SetContent(string content)
    {
        report->content = "<p>" + content + "</p>";
    }

    void SetFooter(string footer)
    {
        report->footer = "<footer>" + footer + "</footer>";
    }

    Report* GetReport()
    {
        return report;
    }
};
