// bshipmain.cpp

#include "battleship.h"

#include <iostream>
#include <string>

using namespace std;

vector<int> getmove(bshipboard *gameboard)
{
    int x,y;
    string input;
    cout << "(A-J)(0-9) > ";
    getline(cin, input);
    x = input[0] - 'A';
    y = input[1] - '0';

    vector<int> move;
    move.push_back(x);
    move.push_back(y);
    return move;
}

void playgame(bshipboard *gameboard)
{
    cout << "Playing!" << endl;
    (gameboard->p1side)->displayboard();
    while (!gameboard->done()) {
        bshipside *currentside = gameboard->p1side;
        if (gameboard->checkturn() == 2) {
            currentside = gameboard->p2side;
        }
        currentside->displayboard();
        vector<int> move = getmove(gameboard);
        int res = gameboard->domove(move);
        if (res == -1) {
            cout << "Invalid move." << endl;
        }
        else if (res == 0) {
            cout << "Miss." << endl;
        }
        else {
            cout << "Hit!!" << endl;
        }
    }
    gameboard->displayfullboard();
}



int main (int argc, char **argv)
{
    cout << "Welcome to Battleship." << endl;

    bshipboard gameboard;
    gameboard.populateboard();
    playgame(&gameboard);

    return 0;
}