#include <iostream>
#include <string>

using namespace std;

// =====================
// 1. Абстрактный класс Document
// =====================
class Document {
public:
    virtual void Open() = 0;  // чисто виртуальный метод
    virtual ~Document() {}
};

// =====================
// 2. Конкретные документы
// =====================

class Report : public Document {
public:
    void Open() {
        cout << "Opening Report document..." << endl;
    }
};

class Resume : public Document {
public:
    void Open() {
        cout << "Opening Resume document..." << endl;
    }
};

class Letter : public Document {
public:
    void Open() {
        cout << "Opening Letter document..." << endl;
    }
};

class Invoice : public Document {
public:
    void Open() {
        cout << "Opening Invoice document..." << endl;
    }
};

// =====================
// 3. Абстрактный создатель (Factory)
// =====================

class DocumentCreator {
public:
    virtual Document* CreateDocument() = 0;
    virtual ~DocumentCreator() {}
};

// =====================
// 4. Конкретные фабрики
// =====================

class ReportCreator : public DocumentCreator {
public:
    Document* CreateDocument() {
        return new Report();
    }
};

class ResumeCreator : public DocumentCreator {
public:
    Document* CreateDocument() {
        return new Resume();
    }
};

class LetterCreator : public DocumentCreator {
public:
    Document* CreateDocument() {
        return new Letter();
    }
};

class InvoiceCreator : public DocumentCreator {
public:
    Document* CreateDocument() {
        return new Invoice();
    }
};

// =====================
// 5. Main — динамический выбор
// =====================

int main() {
    int choice;
    DocumentCreator* creator = NULL;

    cout << "Select document type:" << endl;
    cout << "1 - Report" << endl;
    cout << "2 - Resume" << endl;
    cout << "3 - Letter" << endl;
    cout << "4 - Invoice" << endl;
    cout << "Enter number: ";
    cin >> choice;

    if (choice == 1)
        creator = new ReportCreator();
    else if (choice == 2)
        creator = new ResumeCreator();
    else if (choice == 3)
        creator = new LetterCreator();
    else if (choice == 4)
        creator = new InvoiceCreator();
    else {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    Document* doc = creator->CreateDocument();
    doc->Open();

    delete doc;
    delete creator;

    return 0;
}
