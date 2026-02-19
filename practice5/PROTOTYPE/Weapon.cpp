class Weapon
{
public:
    string name;
    int damage;

    Weapon(string n, int d) : name(n), damage(d) {}

    Weapon* Clone()
    {
        return new Weapon(*this);
    }
};
