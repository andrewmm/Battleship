// battleship.cpp

// Andrew MacKie-Mason
// CMSC 162, University of Chicago
// Project Site: http://brick.cs.uchicago.edu/Courses/CMSC-16200/2012/pmwiki/pmwiki.php/Student/Battleship

#include "battleship.h"

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

//
//
//  bshipAI class functions
//
//

void bshipAI::populateboard()
{
    return;
}

//
//
//  bshipside class functions
//
//

bshipside::bshipside(bshipboard *theboard, int num)
{
    board = theboard;
    int x,y;
    for (x = 0; x < 10; ++x) {
        for (y = 0; y < 10; ++y) {
            positions[x][y] = 0;
            op_positions[x][y] = -1;
        }
    }
    this->AI = NULL;
    playernum = num;
}

int bshipside::addpiece(int x1, int y1, int x2, int y2, int length)
{
    bool nodiag = x1 == x2 or y1 == y2;
    int bigx = max(x1, x2);
    int smallx = min(x1, x2);
    int bigy = max(y1, y2);
    int smally = min(y1, y2);
    bool rightlength = bigx - smallx + bigy - smally == length - 1;
    if (nodiag and rightlength) {
        int x, y;
        for (x = smallx; x <= bigx; ++x) {
            for (y = smally; y <= bigy; ++y) {
                if (positions[x][y] != 0) {
                    return -1;
                }
                positions[x][y] = 1;
            }
        }
        return 0;
    }
    return -1;
}

// Return values:
//  -1: invalid input (either x or y out of range)
//   0: miss
//   1: hit
int bshipside::beattacked(vector<int> coords)
{
    if (coords.size() != 2) {
        return -1;
    }

    int x = coords[0];
    int y = coords[1];
    if (0 <= x and x < 10 and 0 <= y and y < 10) {
        if (positions[x][y] == -1) {
            return -1; // Already hit that piece
        }
        else if (positions[x][y] == 0) {
            return 0;
        }
        else if (positions[x][y] == 1) {
            positions[x][y] = -1;
            return 1;
        }
    }
    else {
        return -1; // invalid position
    }
}

int bshipside::launchattack(vector<int> coords)
{
    if (coords.size() != 2) {
        return -1;
    }

    int x = coords[0];
    int y = coords[1];
    bshipside *op = board->p1side;
    if (playernum == 1) {
        op = board->p2side;
    }

    int result = op->beattacked(coords);

    if (result == -1) {
        return -1;
    }
    else {
        op_positions[x][y] = result;
        return result;
    }
}

bool bshipside::done()
{
    bool isdone = true;
    int x,y;
    for (x = 0; x < 10; ++x) {
        for (y = 0; y < 10; ++y) {
            isdone = isdone and positions[x][y] != 1;
        }
    }
    return isdone;
}

bool bshipside::isAI()
{
    return (AI != NULL);
}

void bshipside::displayboard()
{
    cout << "   A B C D E F G H I J" << endl;
    int x, y;
    for (y = 0; y < 10; ++y) {
        cout << y << "  ";
        for (x = 0; x < 10; ++x) {
            if (op_positions[x][y] == -1) {
                cout << "  ";
            }
            else if (op_positions[x][y] == 0) {
                cout << "- ";
            }
            else {
                cout << "x ";
            }
        }
        cout << endl;
    }
    cout << "----------------------" << endl;
    for (y = 9; y >= 0; --y) {
        cout << y << "  ";
        for (x = 0; x < 10; ++ x) {
            if (positions[x][y] == 0)
                cout << "  ";
            else if (positions[x][y] == 1)
                cout << "* ";
            else
                cout << "! ";
        }
        cout << endl;
    }
    cout << "   A B C D E F G H I J" << endl << endl;
}



//
//
//  bshipboard class functions
//
//

bshipboard::bshipboard()
{
    turn = 1;
    p1side = new bshipside(this, 1);
    p2side = new bshipside(this, 2);
}

bshipboard::~bshipboard()
{
    delete p1side;
    delete p2side;
}

void bshipboard::populateboard()
{
    string names[] = {"aircraft carrier", "battleship", "submarine", "cruiser", "destroyer"};
    int sizes[] = {5, 4, 3, 3, 2};
    bshipside *currentside = p1side;
    int i;
    for (i = 0; i < 2; ++i) {
        if (currentside->isAI()) {
            (currentside->AI)->populateboard();
        }
        else {
            int s = 0;
            while (s < 5) {
                string input;
                int x1,y1,x2,y2;
                currentside->displayboard();
                cout << "Where would you like to put your " << names[s] << " (" << sizes[s] << ")?" << endl << "(A-J)(0-9),(A-J)(0,9) > ";
                getline(cin, input);
                x1 = input[0] - 'A';
                y1 = input[1] - '0';
                x2 = input[3] - 'A';
                y2 = input[4] - '0';

                int result = currentside->addpiece(x1,y1,x2,y2,sizes[s]);
                if (result == 0) {
                    ++s;
                }
            }
        }
        currentside = p2side;
    }
}

void bshipboard::displayfullboard()
{
    bshipside *currentside = p1side;
    int i,x,y;
    for (i = 1; i < 3; ++i) {
        cout << "Player " << i << ":" << endl;
        cout << "   A B C D E F G H I J" << endl;
        for (y = 9; y >= 0; --y) {
            cout << y << "  ";
            for (x = 0; x < 10; ++ x) {
                if (positions[x][y] == 0)
                    cout << "  ";
                else if (positions[x][y] == 1)
                    cout << "* ";
                else
                    cout << "! ";
            }
            cout << endl;
        }
        cout << "   A B C D E F G H I J" << endl << endl;
    }
}

bool bshipboard::done()
{
    return (p1side->done() or p2side->done());
}

int bshipboard::checkturn()
{
    return turn;
}

int bshipboard::domove(vector<int> move)
{
    bshipside *currentside = p1side;
    if (turn == 2) {
        currentside = p2side;
    }

    int result = currentside->launchattack(move);
    if (result == 0) {
        turn = 3-turn;
    }
    return result;
}