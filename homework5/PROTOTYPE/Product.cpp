class Product
{
public:
    string name;
    double price;
    int quantity;

    Product(string n, double p, int q)
        : name(n), price(p), quantity(q) {}

    Product* Clone()
    {
        return new Product(*this);
    }
};
