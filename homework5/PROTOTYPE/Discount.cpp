class Discount
{
public:
    double percent;

    Discount(double p) : percent(p) {}

    Discount* Clone()
    {
        return new Discount(*this);
    }
};
