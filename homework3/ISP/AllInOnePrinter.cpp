class AllInOnePrinter : public IPrinter, public IScanner, public IFax {
public:
    void print(const string& content) override {
        cout << "Printing: " << content << endl;
    }

    void scan(const string& content) override {
        cout << "Scanning: " << content << endl;
    }

    void fax(const string& content) override {
        cout << "Faxing: " << content << endl;
    }
};
