class IFax {
public:
    virtual void fax(const string& content) = 0;
    virtual ~IFax() {}
};
