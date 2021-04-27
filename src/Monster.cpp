#include "../include/Monster.h"
#include "../include/Character.h"


Character character;



Monster::Monster(int fac_base, int fac_type, int char_level)
{
    //generate random monster
    //input randomly generated fac and use character level as base
    this->mon_name=getName(fac_type);
    this->mon_level=getLevel(fac_base, char_level);
    this->mon_hpMax=getHpMax(mon_level, fac_type);
    this->mon_defence=getDefence(mon_level, fac_type);
    this->mon_damage=getDamage(mon_level, fac_type);

}

string Monster::getName(int fac_type)
{
    //random monster with different probabilities for each type
    string Mon_names[5] = {"Ooze", "Cave dweller", "Goblin", "Tiefling", "Guardian"};
    if (fac_type > 95)
    {
        this->mon_name = Mon_names[4];
    }
    else if (fac_type > 80)
    {
        this->mon_name = Mon_names[3];
    }
    else if (fac_type > 55)
    {
        this->mon_name = Mon_names[2];
    }
    else if (fac_type > 30)
    {
        this->mon_name = Mon_names[1];
    }
    else
    {
        this->mon_name = Mon_names[0];
    }

    return this->mon_name;
}

int Monster::getLevel(int fac_base, int char_level)
{
    //generate level slightly higher than player
    this->mon_level = fac_base % 4 + char_level;
    return this->mon_level;
}

int Monster::getDefence(int mon_level, int fac_type)
{
    //generate random defence, varies for different type of monsters
    int type_bonus;
    if (fac_type > 95)
    {
        type_bonus = fac_type / 20;
    }
    else if (fac_type > 80)
    {
        type_bonus = -fac_type / 10;
    }
    else if (fac_type > 55)
    {
        type_bonus = fac_type / 10;
    }
    else if (fac_type > 30)
    {
        type_bonus = -fac_type / 5;
    }
    else
    {
        type_bonus = 0;
    }

    this->mon_defence = mon_level + type_bonus;
    if (this->mon_defence < 0)
    {
        this->mon_defence = mon_level;
    }
    return this->mon_defence;
}


int Monster::getDamage(int mon_level, int fac_type)
{
    //generate random damage, varies for different type of monsters
    int type_bonus;
    if (fac_type > 95)
    {
        type_bonus = fac_type / 15;
    }
    else if (fac_type > 80)
    {
        type_bonus = fac_type / 10;
    }
    else if (fac_type > 55)
    {
        type_bonus = -fac_type / 10;
    }
    else if (fac_type > 30)
    {
        type_bonus = -fac_type / 20;
    }
    else
    {
        type_bonus = 0;
    }

    this->mon_damage = mon_level * 5 + type_bonus;
    if (this->mon_damage <= 0)
    {
        this->mon_damage = mon_level * 2;
    }
    return this->mon_damage;
}

int Monster::getHpMax(int mon_level, int fac_type)
{
    //generate random hp, varies for different type of monsters
    int type_bonus;
    if (fac_type > 95)
    {
        type_bonus = -fac_type / 30;
    }
    else if (fac_type > 80)
    {
        type_bonus = -fac_type / 15;
    }
    else if (fac_type > 55)
    {
        type_bonus = fac_type / 10;
    }
    else if (fac_type > 30)
    {
        type_bonus = -fac_type / 5;
    }
    else 
    {
        type_bonus = 0;
    }

    this->mon_hpMax = mon_level * 10 + type_bonus;
    return this->mon_hpMax;
}

