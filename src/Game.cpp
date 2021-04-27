#include "../include/Game.h"
#include "../include/Character.h"
#include "../include/Monster.h"
#include "../include/Item.h"
#include "../include/Inventory.h"
#include "../include/Events.h"
#include <random>

Game::Game()
{
    //init game varables
    choice = 0;
    playing = true;
    activeCharacter = 0;
    fileName = "characters.txt";
}

Game::~Game()
{
    //dtor
}

void Game::homeMenu()
{
    //home menu, starts when game starts
    //use input choice to functions
    cout << "Welcome, or welcome back, to your story of adventure" << endl;
    cout << "0: New Game" << endl;
    cout << "1: Load Game" << endl;
    cout << "2: Player's manual" << endl;
    cout << "3: Quit Game" << endl;
    cin >> choice;
    
    //handles invalid outputs
    while (cin.good() == 0 || choice > 3)
    {
        cin.clear();
        cout << "What? Say that again." << endl;
        cin.ignore() >> choice;
    }

    switch(choice)
    {
    case 0:
    {
        //start new game
        cin.ignore();
        initGame();
        save();
        Events event;
        event.generateEvent(characters[activeCharacter], 3);

        while (getPlaying())
        {
            //in game menu, return if died/quitted/won
            mainMenu();
        }
        playing = true; //reset after quiting main menu
        break;
    }
      case 1:
        //load saved characters and choose one for play
        load();
        if (this->characters.size()>0) //means at least one Character object is created
        {
            chooseCharacter();
            while (getPlaying())
            {
                mainMenu();
            }
        }
        else
        {
            cout << "you haven't created any character" << endl << endl;
            playing = true;
        }
        break;
    case 2:
        //print manual for confused players
        cout << "This is the manual, it is not that useful" << endl;
        cout << "Start a new game, or load from save slots if you died or quitted" << endl;
        cout << "You can travel and monsters may appear, you could die easily when your level is low" << endl;
        cout << "You can pick up items and use them in a fight, items cannot be reused" << endl;
        cout << "You die, you lose; you escape, you win" << endl;
        cout << "Remeber to use save function frequently, or you lose everything when you die" << endl;
        cout << "0: Go Back" << endl;
        cin >> choice;
        //handle invalid inputs
        while (cin.good() == 0 || choice != 0)
        {
            cin.clear();
            cout << "Are you tired of the manual? Please leave." << endl;
            cin.ignore() >> choice;
        }
        break;
    case 3:
        //quit game
        save();
        playing = false;
        cout << "So long my friend, farewell." << endl;
        break;
    default:
        cout << "What? Say that again." << endl;
        cin >> choice;
    }
}

void Game::mainMenu()
{
    //menu for playing a new/saved character
    //user input choices
    cout << "MAIN MENU" << endl << endl;
    cout << "0: Travel" << endl; //may need seperate function for these options
    cout << "1: Inventory" << endl;
    cout << "2: Character Sheet" << endl;
    cout << "3: Save Progress" << endl;
    cout << "4: Load Progress" << endl;
    cout << "5: Go back to Home" << endl;

    while (cin.good() == 0 || choice > 8)
    {
        cin.clear();
        cout << "Please choose something, pretty please" << endl << endl;
        cin.ignore() >> choice;
    }
    bool valid = false;

    while(!valid)
    {
        cout << "Choice: ";
        cin >> choice;
        if(cin.fail() || choice >7 || choice <0)
        {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            cout << "Invalid Number" << endl;
            continue;
        }
        valid = true;
    }


    switch(choice)
    {
    case 0:
        cout << "Which way do you want to go?" << endl << endl;//travel option
        //travel function, let player encounter events and monsters
        while (getPlaying())
        {
            travel();
        }
        if (characters[activeCharacter]->getHp() > 0)
        {
            //init if player did not die
            playing = true;
        }
        break;
    case 1:
        //print inventory
        cout << "Inventory" << endl << endl;
        if (characters[activeCharacter]->getInventory().size() < 1) {
            cout << "You don't have any item yet" << endl << endl;
        } else {
            characters[activeCharacter]->printItems();
        }

        break;
    case 2:
        //print character stats
        if (this->characters.size()>0) //means at least one Character object is created
        {
            this->characters[activeCharacter]->printStats();
        }
        else
        {
            cout << "you haven't created any character" << endl << endl;
        }
        break;
    case 3:
        //save current progress of player
        save();
        cout << "Save successfully!" << endl << endl;
        break;
    case 4:
        //load saved progress
        load();
        if (this->characters.size()>0)   //means at least one Character object is created
        {
            chooseCharacter();
            while (getPlaying())
            {
                mainMenu();
            }
        }
        else
            cout << "you haven't created any character" << endl << endl;
        break;
    case 5:
        //return to home menu and save
        save();
        playing = false;
        break;
    default:
        cout << "Please choose something, pretty please" << endl << endl;
    }
}

void Game::initGame()
{
    //create a new character with initialized stats
    createNewCharacter();
}

void Game::createNewCharacter()
{
    //restrict user name
    cout << "Enter name for character: ";
    string name = "";
    getline(cin, name);

    Character *c = new Character();
    characters.push_back(c);
    //add new character object to vector
    this->activeCharacter = characters.size() -1;
    characters[activeCharacter]->init(name);
}

void Game::save()
{
    //output file to save character and inventory
    ofstream outFile(this->fileName);

    if(outFile.is_open())
    {
        for(int i=0; i<characters.size(); i++)
        {
            //add the statistics of all created Character objects to the file
            //statistic of each character is stored in a new line
            outFile << this->characters[i]->getAsString() << "\n";
            //add inventory
            string inv = this->characters[i]->getInventoryAsString();
            if (!inv.empty())
                outFile << inv << "\n";
            else
                outFile << "\n";
        }
    }
    outFile.close();
}

void Game::load()
{
    //load saved character file to get character and inventory
    ifstream inFile(fileName);

    this->characters.clear();

    string line = "";
    stringstream str;

    string name = "";
    int level = 0;
    int exp = 0;
    int hp = 0;
    int location=0;

    int defence = 0;
    int damage = 0;

    string weaponName;
    int weaponDamage;
    int weaponDefence;
    string description;

    string itemType;

    if (inFile.is_open())
    {
        //load character stat
        while (getline(inFile, line))
        {
            str.str(line);
            if (!(str >> name
                    >> level
                    >> exp
                    >> hp
                    >>location))
            {
                throw("invalid format input file");
                break;
            }

            Character *temp = new Character(name, level,
                                 exp, hp, location);
            str.clear();
            while (getline(inFile,line))
            {
                if (line.empty()) break;
                str.str(line);
                if (!(str >>
                        itemType >> weaponName >>
                        weaponDamage >> weaponDefence))
                {
                    throw("invalid format input file");
                    break;
                }
                getline(inFile, description);
                Item tempItem = Item(weaponName, weaponDamage, weaponDefence, description);
                temp->addItem(tempItem);
                description.clear();
            }
        this->characters.push_back(temp);
        str.clear();
        line.clear();
        }
    }
    inFile.close();
}

void Game::chooseCharacter()
{
    //choose character from saved characters
    cout << "Select a character: " << endl << endl;

    for (int i = 0; i < this->characters.size(); i++)
    {
        cout << "Enter " << to_string(i) + ": " << endl;
        cout << "Name: " << this->characters[i]->getName() << " Level: " << this->characters[i]->getLevel() << endl;
    }

    cout << endl;
    bool valid = false;

    while (!valid )
    {
        cout << "Choice: ";
        cin >> this->choice;
        //handle invalid data type
        if(cin.fail() || this->choice>=characters.size() ||this->choice<0)
        {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            cout << "Invalid Number" << endl;
            continue;
        }
        valid = true;
    }

    cout << "\n";

    this->activeCharacter = this->choice;
    cout << "You have selected " << this->characters[this->activeCharacter]->getName() << endl << endl;

}

void Game::travel()
{
    //travel function
    //different events and monsters
    //user input to travel or return
    cout << "0: Main menu" << endl;
    cout << "1: Continue walking" << endl;
    int choice;
    cin >> choice;
    while (cin.good() == 0 || choice > 1)
    {
        cin.clear();
        cout << "Do you want to go?" << endl << endl;
        cin.ignore() >> choice;
    }
    switch(choice)
    {
    case 0:
        playing = false;
        break;
    case 1: {
        cin.ignore();
        //random chance to encounter different events
        int roll_fight = rand() % 100;
        if (roll_fight < 40) {
            //auto enter boss fight when player level 10 or up
            if (characters[this->activeCharacter]->getLevel() >= 10)
            {
                Events bossEncouter;
                playing = bossEncouter.generateEvent(characters[this->activeCharacter], -1);
                break;
            }
            else
            {
                //monster event
                Events monsterEncouter;
                playing = monsterEncouter.generateEvent(characters[this->activeCharacter], 0);
            }
        } else {
            //travel a distance and chace to trigger event
            characters[this->activeCharacter]->changeLocation();
            if (characters[this->activeCharacter]->getLocation() % 50 == 0) {
                Events coinFlip;
                coinFlip.generateEvent(characters[this->activeCharacter], 3);
            } else {
               //no event, keep walking
               cout << "Please continue walking." << endl;
            }
        }
        break;
    }
    }
}
