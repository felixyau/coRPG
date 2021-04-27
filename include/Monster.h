#ifndef MONSTER_H
#define MONSTER_H

#include<string>
#include<iostream>
#include <iomanip>

using namespace std;



class Monster
{
    //monster class for random monster generate
    //renew each time when generated, no save/load info
    public:
        Monster(int fac_base, int fac_type, int char_level);

        string getName(int fac_base);
        int getLevel(int fac_base, int char_level);
        int getHpMax(int mon_level, int fac_type);
        int getDamage(int mon_level, int fac_type);
        int getDefence(int mon_level, int fac_type);

        string mon_name;
        int mon_level;
        int mon_hpMax;
        int mon_damage;
        int mon_defence;
};

#endif
