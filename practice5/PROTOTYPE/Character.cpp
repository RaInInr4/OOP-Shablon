class Character
{
public:
    int health;
    int strength;
    Weapon* weapon;
    Armor* armor;
    vector<Skill*> skills;

    Character(int h, int s, Weapon* w, Armor* a)
    {
        health = h;
        strength = s;
        weapon = w;
        armor = a;
    }

    void AddSkill(Skill* skill)
    {
        skills.push_back(skill);
    }

    Character* Clone()
    {
        Character* clone = new Character(
            health,
            strength,
            weapon->Clone(),
            armor->Clone()
        );

        for (int i = 0; i < skills.size(); i++)
        {
            clone->skills.push_back(skills[i]->Clone());
        }

        return clone;
    }
};
