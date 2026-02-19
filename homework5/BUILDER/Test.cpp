int main()
{
    ReportDirector director;

    TextReportBuilder textBuilder;
    director.ConstructReport(&textBuilder);
    Report* textReport = textBuilder.GetReport();
    textReport->Show();

    cout << endl;

    HtmlReportBuilder htmlBuilder;
    director.ConstructReport(&htmlBuilder);
    Report* htmlReport = htmlBuilder.GetReport();
    htmlReport->Show();

    return 0;
}
