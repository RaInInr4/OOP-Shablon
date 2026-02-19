class ReportDirector
{
public:
    void Construct(IReportBuilder* builder)
    {
        builder->SetHeader("=== REPORT HEADER ===");
        builder->SetContent("Main Content");
        builder->AddSection("Section 1", "Section content");
        builder->SetFooter("=== END ===");
    }
};
