#include <iostream>

#include"include/Game.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Game game;

    ifstream inFile(game.getFileName());

    //check if the file is empty
    //load progress otherwise
    if (!(inFile.peek()==inFile.eof())) {
        game.load();
    }
    inFile.close();

    while (game.getPlaying())
    {
    //call home menu when game start, exit when player quit/die/win
        game.homeMenu();
    }
    return 0;
}
