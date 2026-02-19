#include <vector>

class Order
{
public:
    vector<Product*> products;
    Discount* discount;
    double deliveryCost;
    string paymentMethod;

    Order(double delivery, string payment)
    {
        deliveryCost = delivery;
        paymentMethod = payment;
        discount = nullptr;
    }

    void AddProduct(Product* product)
    {
        products.push_back(product);
    }

    void SetDiscount(Discount* d)
    {
        discount = d;
    }

    Order* Clone()
    {
        Order* newOrder = new Order(deliveryCost, paymentMethod);

        for (int i = 0; i < products.size(); i++)
        {
            newOrder->products.push_back(products[i]->Clone());
        }

        if (discount != nullptr)
            newOrder->discount = discount->Clone();

        return newOrder;
    }

    void Show()
    {
        cout << "Delivery: " << deliveryCost << endl;
        cout << "Payment: " << paymentMethod << endl;

        for (int i = 0; i < products.size(); i++)
        {
            cout << products[i]->name << " "
                 << products[i]->price << " x "
                 << products[i]->quantity << endl;
        }

        if (discount != nullptr)
            cout << "Discount: " << discount->percent << "%" << endl;
    }
};
