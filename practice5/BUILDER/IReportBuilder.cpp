class IReportBuilder
{
public:
    virtual void SetHeader(string header) = 0;
    virtual void SetContent(string content) = 0;
    virtual void SetFooter(string footer) = 0;
    virtual void AddSection(string name, string content) = 0;
    virtual void SetStyle(ReportStyle style) = 0;
    virtual Report* GetReport() = 0;

    virtual ~IReportBuilder() {}
};
