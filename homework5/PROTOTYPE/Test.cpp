int main()
{
    Order* order1 = new Order(10, "Card");
    order1->AddProduct(new Product("Laptop", 1000, 1));
    order1->SetDiscount(new Discount(10));

    Order* order2 = order1->Clone();
    order2->paymentMethod = "Cash";

    order1->Show();
    cout << endl;
    order2->Show();

    return 0;
}
