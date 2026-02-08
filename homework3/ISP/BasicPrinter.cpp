class BasicPrinter : public IPrinter {
public:
    void print(const string& content) override {
        cout << "Printing: " << content << endl;
    }
};
