class IScanner {
public:
    virtual void scan(const string& content) = 0;
    virtual ~IScanner() {}
};
