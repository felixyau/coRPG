#include "../include/Character.h"

Character::Character()
{
    //initialize basic statistics for newly created Character
    this->name="";
    this->level=1;
    this->exp=0;
    this->expNext= static_cast<int>((50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + (17 * level) - 12))+100; //formula for unlimited level copied from the internet

    this->inventory = Inventory();

    this->hpMax= 20 + this->level * 2;
    this->hp=this->hpMax;
    this->damage= this->hpMax / 2 + level * 2;
    this->defence= this->damage / 4 + level / 2;


}

Character::Character(string name, int level, int exp, int hp, int location)
{
    //initialize basic statistics for newly created Character
    this->name= name;
    this->level=level;
    this->exp=exp;
    this->expNext= static_cast<int>((50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + (17 * level) - 12))+100; //formula for unlimited level copied from the internet

    this->inventory = Inventory();
    this->hp=hp;
    this->hpMax= 20 + level * 10;

    this->damage= this->hpMax / 2 + level * 2;
    this->defence= this->damage / 4 + level / 2;
    this->location = location;
}


Character::~Character()
{
    //dtor
}

void Character::init(string name)
{
    this->name = name;
}

void Character::printStats()
{
    cout << "=Character Stats=" << endl << endl;
    cout << "Name: " << this->name << endl;
    cout << "Level: " << this->level << endl;
    cout << "Exp: " << this->exp << endl;
    cout << "Exp to next level: " << this->expNext << endl;
    cout << "HP: " << this->hp << endl;
    cout << "Damage: " << this->damage << endl;
    cout << "Defence: " << this->defence << endl << endl;
}

string Character::getAsString() const
{
    //store all the statistics of a Character as string
    //used for saving progress
    return this->name + " "
           + to_string(this->level) + " "
           + to_string(this->exp) + " "
           + to_string(this->hp) + " "
           + to_string(this->location);
}

void Character::levelUp(int exp_drop)
{
    //input exp from monster fight drops
    //level up player till exp is not enough
    this->exp += exp_drop;
    //expNext is the exp require to level up
    while (this->exp>=this->expNext)
    {
        this->exp -= this->expNext;
        this->level++;
        //increase the exp needed to level up
        this->expNext = static_cast<int>((50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + (17 * level) - 12));
        cout << "Level up! You are now level " << this->level << endl;
        cout << this->expNext - this->exp << "left till next level" << endl << endl;
    }
    this->hpMax = 20 + level * 10;
    this->hp = this->hpMax;
}

string Character::getInventoryAsString()
{
    //get inventory as a string for save/load
    string inv="";

    for (int i = 0; i < this->inventory.size(); i++) {
        inv += to_string(i) + ": " + this->inventory[i].toString() + "\n";
    }

    return inv;

}
