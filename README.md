text-basedGame

By Yau Lok Hang and Lai Wing Man Jasmine

**Description** 

CompletelyOriginalRPG is a mysterious adventure game full of unimaginable encouters.
 You play as an explorer who has been trapped in a dungeon. John must explore the environment and find his way back home. 

Enter a strange and unexplored dungeon full of dangers, monsters, and surprises. Fight and discover to survive monster attacks and escape.

**Why RPG**

We love rpg. There's just so much variety in there. And we learnt a lot. Since there are many elemets, it allows us to apply all coding requirements.

**Mechanism**

All the actions are performed by entering a certain word/letter, which the word/letter will be provided in game. There's a home menu that allow you to create character or load progress. Then there's a mainMenue that allow you to perform different actions like travelling, check character information, save/load progress. 
To traverse the dungeon you enter '0' when you're in the main menu and '1' to make a move. Each time you make a move there will be a chance that you will encouter a event, including monster fight, buffs, etc. It's somewhat like playing monopoly. 
The fights are turn-based and you will enter specific number to perform any action like attacking, escape, etc.
(ASSUMPTION: We expect players to save their progress before closing the console window or leaving, or there will be a chance that the progress is not saved.)

**Game rules**

You lost when your hp dropped to zero. There are events that will lower your hp like monsters attack. 
You win when you defeat the boss. The boss will appear after you reached certain level.

**Features**

- Random events like item drops and monster attack 
  - The list of items and monsters is fixed along with their statistics, but they will be randomly picked. Random item drop and the monster that the player will be fighting. All these require the generation of random game sets or events(coding requirement 1). Of couse monsters generated are not just random but also depend on character's level.

- Turn-based fight with monsters
  - In a turn, Players can choose to attack, use item, or flee. The fighting status like hp, remaining moves in the turn are stored in different data structures(coding requirement 2). Players win the fight and return to the dungeon interface when monsters’ hp drops to zero, with a chance of dropping items. Players lose when self hp drops to zero. When there are no moves remaining, the monster flees and players return to the dungeon interface. 

- An inventory system that stores the items collected by the player. 
  - The inventory make use of vector to store items, which requires the use of data struture(coding requirement 2). Players can also checkt the inventory by printing time.
  - We prepared a item sheet named item_list.txt. Reading the txt file to create item in game requires file input/output(coding requirement 4).

- Players can save their progress
  - You can create as many characters as you want. And choose the character to play with anytime you want by loading.
  - When they die, win, or exit the game they can choose to replay the game at the start or resume the game at any save slot. Their items acquired in the dungeon will be saved that makes use of data structures(coding requirement 2) and  requires file input/output(coding requirement 4).
  - We created a characters vector which is convient for loading progress, and allow us to freely switching characters(coding requirement 2).

We are trying to implment our project in a form of OOP. For the each class there will be a header file and cpp file, and there is a main.cpp(coding requirement 5). 

For (coding requirement 3) we didn't make use of it much because we decided that vectors are more convinient. ItemArr in inventory was a dyanamic array but we changed it to a vector. But, when loading progress, NEW character objects will be generated which requires Dynamic memory management(coding requirement 3). 

**Set Up**

After getting all the source files, use makefile to generate main with following command:

make main

Then, execute main with following command: 

./main

The game shall start with a welcome menu.

**Quick start**

- press 0 to create a character
- enter a name
You are set!
