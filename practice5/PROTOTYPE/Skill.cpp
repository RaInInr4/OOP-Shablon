class Skill
{
public:
    string name;

    Skill(string n) : name(n) {}

    Skill* Clone()
    {
        return new Skill(*this);
    }
};
