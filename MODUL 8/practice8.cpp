#include <iostream>
#include <string>

using namespace std;

/* ---------------- DECORATOR PATTERN ---------------- */

// Интерфейс
class IReport {
public:
    virtual string Generate() = 0;
};

// Sales report
class SalesReport : public IReport {
public:
    string Generate() {
        return "Sales Report: ProductA 100$, ProductB 200$";
    }
};

// User report
class UserReport : public IReport {
public:
    string Generate() {
        return "User Report: User1, User2, User3";
    }
};

// Абстракт декоратор
class ReportDecorator : public IReport {
protected:
    IReport* report;

public:
    ReportDecorator(IReport* r) {
        report = r;
    }
};

// Date filter
class DateFilterDecorator : public ReportDecorator {
public:
    DateFilterDecorator(IReport* r) : ReportDecorator(r) {}

    string Generate() {
        return report->Generate() + "\nFiltered by date";
    }
};

// Sorting
class SortingDecorator : public ReportDecorator {
public:
    SortingDecorator(IReport* r) : ReportDecorator(r) {}

    string Generate() {
        return report->Generate() + "\nSorted by sales amount";
    }
};

// CSV export
class CsvExportDecorator : public ReportDecorator {
public:
    CsvExportDecorator(IReport* r) : ReportDecorator(r) {}

    string Generate() {
        return report->Generate() + "\nExported to CSV";
    }
};

// PDF export
class PdfExportDecorator : public ReportDecorator {
public:
    PdfExportDecorator(IReport* r) : ReportDecorator(r) {}

    string Generate() {
        return report->Generate() + "\nExported to PDF";
    }
};


/* ---------------- ADAPTER PATTERN ---------------- */

// Ішкі интерфейс
class IInternalDeliveryService {
public:
    virtual void DeliverOrder(string orderId) = 0;
    virtual string GetDeliveryStatus(string orderId) = 0;
};

// Ішкі доставка
class InternalDeliveryService : public IInternalDeliveryService {
public:
    void DeliverOrder(string orderId) {
        cout << "Internal delivery for order " << orderId << endl;
    }

    string GetDeliveryStatus(string orderId) {
        return "Delivered by internal service";
    }
};

// Сыртқы сервис A
class ExternalLogisticsServiceA {
public:
    void ShipItem(int itemId) {
        cout << "ServiceA shipping item " << itemId << endl;
    }

    string TrackShipment(int shipmentId) {
        return "Tracking shipment in ServiceA";
    }
};

// Adapter A
class LogisticsAdapterA : public IInternalDeliveryService {

private:
    ExternalLogisticsServiceA service;

public:
    void DeliverOrder(string orderId) {
        int id = stoi(orderId);
        service.ShipItem(id);
    }

    string GetDeliveryStatus(string orderId) {
        int id = stoi(orderId);
        return service.TrackShipment(id);
    }
};

// Сыртқы сервис B
class ExternalLogisticsServiceB {
public:
    void SendPackage(string info) {
        cout << "ServiceB sending package " << info << endl;
    }

    string CheckPackageStatus(string code) {
        return "Tracking package in ServiceB";
    }
};

// Adapter B
class LogisticsAdapterB : public IInternalDeliveryService {

private:
    ExternalLogisticsServiceB service;

public:
    void DeliverOrder(string orderId) {
        service.SendPackage(orderId);
    }

    string GetDeliveryStatus(string orderId) {
        return service.CheckPackageStatus(orderId);
    }
};

// Factory
class DeliveryServiceFactory {
public:

    static IInternalDeliveryService* CreateService(string type) {

        if (type == "internal")
            return new InternalDeliveryService();

        if (type == "A")
            return new LogisticsAdapterA();

        if (type == "B")
            return new LogisticsAdapterB();

        return NULL;
    }
};


/* ---------------- MAIN ---------------- */

int main() {

    cout << "===== DECORATOR PATTERN =====" << endl;

    IReport* report = new SalesReport();

    report = new DateFilterDecorator(report);
    report = new SortingDecorator(report);
    report = new CsvExportDecorator(report);

    cout << report->Generate() << endl;


    cout << "\n===== ADAPTER PATTERN =====" << endl;

    IInternalDeliveryService* delivery;

    delivery = DeliveryServiceFactory::CreateService("A");

    delivery->DeliverOrder("123");

    cout << delivery->GetDeliveryStatus("123") << endl;

    return 0;
}