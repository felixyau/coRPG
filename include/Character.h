#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include<iostream>
#include <cmath>
#include <iomanip>

#include "Inventory.h"

using namespace std;

class Character
{
    //character stats stored in class, and class functions
    public:
        Character();
        Character(string name, int level, int exp, int hp, int location);
        virtual ~Character(); //ignore for now
        void init(string name);
        void printStats();
        void levelUp(int exp_drop);
        string getAsString() const;
        string getInventoryAsString();
        void addItem(Item &item, int quantity=1) { this->inventory.addItem(item); }
        void printItems() { this->inventory.printItems(); }
        void changeLocation() { location+=10;}
        void changeHp(int x) { hp += x;}

        //all these functions allow us to get character statistics outside the class Character

        int &getLocation() {return this->location;}
        int &getHp() {return this->hp;}
        string &getName() {return this->name;}
        int &getLevel() {return this->level;}
        int &getExp() {return this->exp;}
        int &getNextLExp() {return this->level;}

        int &getHpMax() {return this->hpMax;}
        int &getDamage() {return this->damage;}
        int &getDefence() {return this->defence;}

        Inventory &getInventory() { return this->inventory; }



    private:
        int hp;
        int location;
        string name;
        int level;
        int exp;
        int expNext;

        Inventory inventory;

        int hpMax;
        int damage;
        int defence;
};

#endif
