#include "../include/Inventory.h"
#include <vector>


Inventory::Inventory()
{

}


Inventory::~Inventory()
{

}

Item& Inventory::operator[](int index)
{
	//return a item object in inventory
	return this->itemArr[index];
}

void Inventory::addItem(Item &item)
{
    //add new item to inventory
    //dont add if inventory already has same item
    for (Item &i: itemArr) {
        if (i.getName()==item.getName())
        {
            cout << "Oh, you already have " << item.getName() << "? No more for you then" << endl;
            return;
        }
    }
    cout << "New item: " << item.getName() << "! Now in your inventory" << endl;
    this->itemArr.push_back(item);
}

void Inventory::removeItem(int index)
{
    //remove an item from inventory
    this->itemArr.erase (this->itemArr.begin() + index);
}

void Inventory::printItems()
{
    //print items in the inventory
    int j = 0;
    for (Item &i:itemArr) {
        cout << j << ": " << "Item Name: " << i.getName() << endl;
        j++;
    }
}
