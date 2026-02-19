class ReportDirector
{
public:
    void ConstructReport(IReportBuilder* builder)
    {
        builder->SetHeader("Sales Report");
        builder->SetContent("Total revenue: 10000$");
        builder->SetFooter("2026 Company");
    }
};
