#ifndef GAME_H
#define GAME_H

#include<ctime>
#include <vector>
#include <fstream>
#include<sstream>
#include <limits>
#include <random>
#include "Character.h"
#include "Events.h"
#include "Item.h"
#include "Inventory.h"

using namespace std;


class Game
{
    //game functions and variables in class
    public:
        Game();
        virtual ~Game();//ignore for now
        void initGame();
        void homeMenu(); //added this
        void mainMenu();

        void travel();

        void createNewCharacter();
        void save();
        void load();
        void chooseCharacter();

        bool getPlaying() const {
        return this->playing;}
        string getFileName() {
        return this->fileName;}

    private:
        int choice;
        bool playing;
        //index of the newest added Character object in the character vector
        int activeCharacter;
        //characters is a vector contains all the Character object created
        vector <Character*> characters;
        string fileName;

};

#endif
