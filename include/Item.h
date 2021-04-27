#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Item
{
    //item stats for random items and add to inventory
public:
    Item(string name, int damage, int defence, string description);
    ~Item();
    string getName() { return name; }
    int getDamage() { return damage; }
    int getDefence() { return defence; }
    string toString();
private:
    string name;
    int quantity;
    int damage;
    int defence;
    string description;
};

class item {
public:
    item(int fac);
    string i_name;
    string i_description;
    int i_damage;
    int i_defence;
};

#endif
