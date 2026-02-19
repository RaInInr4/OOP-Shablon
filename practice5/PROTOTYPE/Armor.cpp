class Armor
{
public:
    string name;
    int defense;

    Armor(string n, int d) : name(n), defense(d) {}

    Armor* Clone()
    {
        return new Armor(*this);
    }
};
