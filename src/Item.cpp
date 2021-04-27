#include "../include/Item.h"
#include <fstream>

Item::Item(string name, int damage, int defence, string description)
{
	//Item value from input item values
	this->name=name;
	this->damage= damage;
	this->defence= defence;
	this->description = description;
}

Item::~Item()
{
    //dtor
}

string Item::toString()
{
    //return an item as a string
    return this->name + " "
           + to_string(this->damage) + " "
           + to_string(this->defence) + "\n"
           + this->description;
}

item::item(int fac)
{
    //input a random fac
    //read item_list.txt for item info
    //add a item on the same line as fac
    char item_list[50] = "item_list.txt";
    ifstream fin;
    fin.open(item_list);

    if ( fin.fail() ){
        cout << "file not found" << endl;
        exit(1);
    }
    fin.clear();
    fin.seekg(51 * fac);
    fin >> this->i_name >> this->i_damage >> this->i_defence;
    getline(fin, this->i_description, '.');
    this->i_description = this->i_description.substr(1);
    fin.close();
}
