#include "../include/Events.h"

Events::Events()
{
    //ctor
}

Events::~Events()
{
    //dtor
}



bool Events::generateEvent(Character *character,int x)
{
    //input character info and x for event option
    //generate said event, return false if died 
    switch(x)
    {
    case -1:
        return this->bossEncouter(character);
        break;
    case 0:
        return this->monsterEncouter(character);
    case 1:
        this->itemDrop(character);
        break;
    case 2:
        this->potion(character);
        break;
    case 3:
        this->coinFlip(character);
        break;

    default:
        break;
    }
    return true;
}

void Events::itemDrop(Character *character)
{
    //input character info
    //drop random items and equip to inventory if it wasnt in inventory
    int item_c = rand() % 3 + 1, item_d;
    for (int j = 0; j < item_c; ++j)
    {
        item_d = rand() % 20;
        bool item_u = true;
        item i(item_d);
        Item item(i.i_name, i.i_damage, i.i_defence, i.i_description);
        cout << "Whoa, you found " << i.i_description << endl;
        character->getInventory().addItem(item);
    }
}

void Events::potion(Character *character)
{
    //input character info
    //potion event
    cout << "You have found a purple potion. Do you want to drink it?" << endl;
    bool valid = false;

    while(!valid)
    {
        char choice;
        //use input for drink potion or not
        cout << "y/n: ";
        cin >> choice;
        if(cin.fail() || (choice!='y' && choice!='n'))
        {
            cin.clear();
            cin.ignore(numeric_limits<char>::max(), '\n');
            cout << "Invalid Input" << endl;
            continue;
        }
        valid = true;

        //chance for hp loss or gain
        int i = rand() % (( 100 ));
        if (choice=='n')
        {
            cout << "Ok then" << endl;
            return ;
        }
        if (i<50)
        {
            cout << "It tastes terrible" << endl;
            int hpLoss=character->getHp()*0.1;
            cout << "HP - " << hpLoss << "!" << endl;
            character->changeHp(-hpLoss);
            return;
        }
        cout << "It's actually a life potion" << endl;
        int hpGain=character->getHp()*0.4;
        cout << "HP + " << hpGain << "!" << endl;
        character->changeHp(hpGain);
    }
}

void Events::coinFlip(Character *character)
{
    //input character info
    //coin flip event
    cout << "You saw a guy holding a bunch of pennies. You are curious and walk near. He says:\"I will flip a coin, if you guess which side lands you will be rewarded.\"" << endl << endl;

    bool valid = false;

    while(!valid)
    {
        //use input to guess coin flip results
        //output for different guess
        cout << "Your guess(head/tail): ";
        string choice;
        getline(cin, choice);
        if (choice!="head"&&choice!="tail")
        {
            cout << "Invalid Input" << endl;
            continue;
        }
        valid = true;
        if (choice=="tail")
        {
            cout << "When you are about to walk away, you see that both sides of the pennies are the same. But the guy disappeared." << endl << endl;
            return;
        }
    }
    //correct guess output
    cout << "You have got a map" << endl;
    cout << "There is a star on the map, do you want to go to that location?" << endl;
    valid = false;
    while(!valid)
    {
        //user input for going to map location or not
        //return if not
        char choice;
        cout << "y/n: ";
        cin >> choice;
        if(cin.fail() || (choice!='y' && choice!='n'))
        {
            cin.clear();
            cin.ignore(numeric_limits<char>::max(), '\n');
            cout << "Invalid Input" << endl;
            continue;
        }
        valid = true;
        if (choice=='n')
        {
            cout << "really?" << endl << "ok then" << endl << endl;
            return;
        }
    }
    //player travel to map location
    //quiz for winning a price
    //user input answer
    cout << "You entered a room, and there's only a iphone there." << endl;
    cout << "You pick up the phone and a line appears on the screen." << endl;
    cout << "COUNT TO TEN" << endl;

    valid = false;

    while(!valid)
    {
        cout << "First Number: ";
        int x;
        cin >> x;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<char>::max(), '\n');
            cout << "Invalid Input" << endl;
            continue;
        }
        valid = true;
        if (x!=0)
        {
            cout << "Failed!" << endl << endl;
            return;
        }
        //win new price if quiz correct
        cout << "You are a qualified programmer. Take the reward" << endl;
        cout << "You got a new item: iphone 12" << endl << endl;
        Item iphone12 = Item("iphone12", 11, 11, "the newest version of iphone");
        character->addItem(iphone12);
    }
}

void Events::puzzle()
{

}

int Events::roll_dice() //for generating random monster values
{
    random_device seed;
    mt19937 roll(seed());
    uniform_int_distribution<int> dice(0, 99);
    return dice(roll);
}

//return false if lose
bool Events::monsterEncouter(Character *character)
{
    //generate random monster
    int fac_base = roll_dice(), fac_type = roll_dice();
    int attack;
    bool playing = true;
    Monster monster(fac_base, fac_type, character->getLevel());
    cout << endl << "Oh no!" << endl;
    cout << "You encounter a level " << monster.mon_level << ' ' << monster.mon_name << '!' << endl;
    cout << "It is a fight between human and monster! There's no way to run!" << endl << endl;
    while (playing)
    {
        //user input choices to fight monster
        cout << "Monster: " << monster.mon_name << endl;
        cout << "Level: " << monster.mon_level << endl;
        cout << "Damage: " << monster.mon_damage << endl;
        cout << "HP: " << monster.mon_hpMax << endl;
        cout << "0: Character sheet" << endl;
        cout << "1: Attack" << endl;
        cout << "2: Items" << endl;
        cout << "3: Spare" << endl;
        int choice = 0, i;
        bool tmp = false;
        cin >> choice;
        while (cin.good() == 0 || choice > 4)
        {
            cin.clear();
            cout << "Concentrate! You are in a fight!" << endl << endl;
            cin.ignore() >> choice;
        }
        if (choice == 0)
        {
            character->printStats();
            continue;
        }

        switch(choice)
        {
        case 1:
            //attack monster
            attack = character->getDamage() - monster.mon_defence;
            if (attack > 0)
            {
                monster.mon_hpMax -= attack;
                cout << "You attacked the " << monster.mon_name << "! " << endl;
                cout << monster.mon_name << "'s HP -" << attack << endl;
            }
            else
            {
                monster.mon_hpMax -= 1;
                cout << "You attacked the " << monster.mon_name << "..." << endl;
                cout << monster.mon_name << "'s HP -1" << endl;
            }
            cout << endl;
            break;
        case 2:
            //use item to attack/protect user
            //user input to choose item
            if (character->getInventory().size() == 0) {
                cout << "Nothing to choose! Think again" << endl;
                attack = character->getDamage() - monster.mon_defence * 2;
                if (attack > 0)
                {
                    monster.mon_hpMax -= attack;
                    cout << "You was too caught up in your inventory, but still managed to attack the " << monster.mon_name << "! " << endl;
                    cout << monster.mon_name << "'s HP -" << attack << endl;
                }
                else
                {
                    monster.mon_hpMax -= 1;
                    cout << "You was too caught up in your inventory, but still managed to attack the " << monster.mon_name << "..." << endl;
                    cout << monster.mon_name << "'s HP -1" << endl;
                }
                break;
            }
            cout << "Choose somthing to use from your inventory: " << endl; //to be added
            character->getInventory().printItems();
            cin >> i;
            tmp = true;
            attack = character->getDamage() - monster.mon_defence + character->getInventory().operator[](i).getDamage();
            if ( character->getInventory().operator[](i).getDefence() > 0)
            {
                cout << "You used" << character->getInventory().operator[](i).getName() << " to prptect yourself!" << endl;
            }

            if (attack > 0)
            {
                if (character->getInventory().operator[](i).getDamage() > 0)
                {
                    cout << "You used " << character->getInventory().operator[](i).getName() << " to attack the " << monster.mon_name << '!' << endl;
                }
                else
                {
                    cout << "You attacked the " << monster.mon_name << "..!" << endl;
                }
                monster.mon_hpMax -= attack;
                cout << monster.mon_name << "'s HP -" << attack << endl;
            }
            else
            {
                monster.mon_hpMax -= 1;
                cout << "You attacked the " << monster.mon_name << "..." << endl;
                cout << monster.mon_name << "'s HP -1" << endl;
            }
            cout << endl;
            break;
        case 3:
            //spare monster, succeed when monster hp is low enough
            //monster flee if spared, else monster will attack
            cout << "How kind, " << character->getName() << " decided to make peace with the " << monster.mon_name << endl;
            if (character->getDamage() > monster.mon_hpMax * 1.5)
            {
                cout << "Yes, the monster shall make peace with you" << endl;
                cout << "The fighting is no more, now go on!" << endl << endl;
                playing = false;
            }
            else
            {
                cout << "But the monster thought otherwise, they insisted to fight" << endl << endl;
            }
            break;
        }
        if (!playing)
        {
            //spared successfully
            playing = true;
            break;
        }
        if (monster.mon_hpMax <= 0)
        {
            //defeat monster when its hp drops to zero
            //drop items and exp
            //go back to traveling in dungeon
            cout << "You defeated " << monster.mon_name << "! Or at least, you survived" << endl;
            if (tmp) {
                character->getInventory().removeItem(i);
            }
            itemDrop(character);
            int exp_drop = (rand() % 10) + monster.mon_level * 50;
            cout << "As the dead body of the monster slowly vanished, you gained " << exp_drop << " exp!" << endl;
            character->levelUp(exp_drop);
            cout << endl;
            break;
        }
        //monster attack if not spared or defeated
        cout << monster.mon_name << " attacked you!" << endl;
        attack = monster.mon_damage - character->getDefence();
        if (tmp) {
            //item lost after one round use
            attack -= character->getInventory().operator[](i).getDefence();
            character->getInventory().removeItem(i);
            tmp = false;
        }
        if (attack > 0)
        {
            character->changeHp(-attack);
            cout << character->getName() << "'s hp -" << attack << endl;
        }
        else
        {
            cout << character->getName() << "'s hp -0" << endl;
        }
        cout << endl;
        if (character->getHp() <= 0)
        {
            cout << "You was defeated by " << monster.mon_name << endl;
            cout << "Sorry, you are now dead, try again next time" << endl << endl;
            //delete save load here
            playing = false;
            break;
        }
    }
    //false if player died, and go back to home menu
    return playing;
}

bool Events::bossEncouter(Character *character)
{
    //boss fight, similar to monster fight 
    //not random, appear when player level 10 or up
    //win if boss died, otherwise lose
    //cant spare
    int attack;
    bool playing = true;
    string boss_name = "Dungeon Master";
    int boss_level = 0, boss_damage = 50, boss_defence = 0, boss_hp = 500;
    cout << endl << "Oh no!" << endl;
    cout << "You encounter a level " << boss_level << ' ' << boss_name << '!' << endl;
    cout << "The time has come...I have watched you grow...but now...!" << endl << endl;
    cout << "It is a fight between you and me! There's no way to run!" << endl << endl;
    while (playing)
    {
        cout << "Monster: " << boss_name << endl;
        cout << "Level: " << boss_level << endl;
        cout << "Damage: " << boss_damage << endl;
        cout << "HP: " << boss_hp << endl;
        cout << "0: Character sheet" << endl;
        cout << "1: Attack" << endl;
        cout << "2: Items" << endl;
        cout << "3: Spare" << endl;
        int choice = 0, i;
        bool tmp = false;
        cin >> choice;
        while (cin.good() == 0 || choice > 4)
        {
            cin.clear();
            cout << "Concentrate! You are in a fight! Against me!" << endl << endl;
            cin.ignore() >> choice;
        }
        if (choice == 0)
        {
            character->printStats(); 
            cout << endl;
            continue;
        }

        switch(choice)
        {
        case 1:
            boss_hp -= character->getDamage();
                cout << "You attacked the " << boss_name << "! " << endl;
                cout << "See? I have no defence..." << endl;
                cout << boss_name << "'s HP -" << character->getDamage() << endl << endl;
            break;
        case 2:
            if (character->getInventory().size() == 0)
            {
                cout << "Nothing to choose! I kept your record, nice and claen!" << endl;
                boss_hp -= character->getDamage()/2;
                    cout << "You was too caught up in your inventory, but still managed to attack the " << boss_name << "! " << endl;
                    cout << "Don't hit me with your inventory bag!" << endl;
                    cout << boss_name << "'s HP -" << character->getDamage()/2 << endl;break;
            }
            cout << "Choose somthing to use from your inventory: " << endl; //to be added
            character->getInventory().printItems();
            cin >> i;
            tmp = true;
            attack = character->getDamage() + character->getInventory().operator[](i).getDamage();
            if ( character->getInventory().operator[](i).getDefence() > 0)
            {
                cout << "You used " << character->getInventory().operator[](i).getName() << " to protect yourself!" << endl;
            }

            if (character->getInventory().operator[](i).getDamage() > 0)
            {
                cout << "You used " << character->getInventory().operator[](i).getName() << " to attack the " << boss_name << '!' << endl;
            }
            else
            {
                cout << "You attacked the " << boss_name << "..!" << endl;
            }
            boss_hp -= attack;
            cout << boss_name << "'s HP -" << attack << endl << endl;
            break;
        case 3:
            cout << "How kind, " << character->getName() << " decided to make peace with the " << boss_name << endl;
            cout << "...Seriously? just move on to next round" << endl << endl;
            break;
        }
        if (boss_hp <= 0)
        {
            cout << "You defeated " << boss_name << "! You truly, truly survived" << endl << endl;
            if (tmp) {
                character->getInventory().removeItem(i);
            }
            int exp_drop = 0;
            cout << endl << "Fine, you gained " << exp_drop << " exp" << endl;
            cout << "Don't look at me now, go over my dead body and leave..." << endl;
            cout << "Don't forget to close the door, it is cool outside in the surface world" << endl;
            cout << "Feel empty yet? play the game again I dare you" << endl;
            cout << "or just go do something more productive...like, getting off your computer" << endl;
            cout << "You win. Bye bye, bye bye" << endl << endl;
            exit(0);
            break;
        }

        cout << boss_name << " attacked you!" << endl;
        attack = boss_damage;
        if (tmp) {
            attack -= character->getInventory().operator[](i).getDefence();
            character->getInventory().removeItem(i);
            tmp = false;
        }
        character->changeHp(-attack);
        cout << character->getName() << "'s hp -" << attack << endl;
        cout << "Haha, no defence! or some from your item, I guess" << endl << endl;

        if (character->getHp() <= 0)
        {
            cout << endl << "You was defeated by " << boss_name << endl;
            cout << "Dead! That's how you are now!" << endl;
            cout << "Go load your game and fight me again!" << endl;
            cout << "Wait no, find some magic keys or something, I hate fights" << endl;
            cout << "Forgot to save?...bad news for you, bad news" << endl << endl;
            
            exit(0);
            break;
        }
    }
    return playing;
}
