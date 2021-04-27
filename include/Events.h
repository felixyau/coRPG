#ifndef EVENTS_H
#define EVENTS_H

#include <limits>
#include <random>
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "Inventory.h"

class Events
{
    //different event functions stored in class
    public:
        Events();
        bool generateEvent(Character *character, int typeOfEvent);
        virtual ~Events();
        void potion(Character *character);
        void itemDrop(Character *character);
        int roll_dice();
        bool monsterEncouter(Character *character);
        bool bossEncouter(Character *character);
        void coinFlip(Character *character);
        void puzzle();
    private:
};

#endif // EVENTS_H
