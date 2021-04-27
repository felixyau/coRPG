#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <vector>

class Inventory
{
public:
    //inventory functions to manipulate item in inventory
    Inventory();
    ~Inventory();
    void addItem(Item &item);
    void removeItem(int index);
    void printItems();
    Item& operator[](int index);
    int size() { return itemArr.size(); }
private:
    //pointer to the pointer array
    //check constructor of Inventory in inventory.cpp
    vector <Item> itemArr;
    //size of the dynamic array (itemArr)
    void init(const int from=0);
    void expand();
};

#endif
