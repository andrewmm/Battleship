// battleship.h

// Andrew MacKie-Mason
// CMSC 162, University of Chicago
// Project Site: http://brick.cs.uchicago.edu/Courses/CMSC-16200/2012/pmwiki/pmwiki.php/Student/Battleship

#include <vector>

#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

class bshipboard;
class bshipside;

class bshipAI
{
    private:
        bshipside *our_side;
    public:
        std::vector<int> get_move();
        void populateboard();

        bshipAI(bshipside *ourside); // constructor
};

class bshipside
{
    private:
        bshipboard *board;
        int playernum;
        int positions[10][10]; // 0 = no piece, 1 = piece, -1 = hit piece
        int op_positions[10][10]; // 0 = no piece, 1 = hit piece, -1 = no information
    public:
        bshipAI *AI;
        int addpiece(int x1, int y1, int x2, int y2, int length);
        int beattacked(std::vector<int> coords);
        int launchattack(std::vector<int> coords);
        bool done();
        bool isAI();
        void displayboard();

        bshipside(bshipboard *theboard, int num); // constructor
};

class bshipboard
{
    private:
        int turn; // 1 or 2
    public: 
        bshipside *p1side;
        bshipside *p2side;

        bshipboard(); // constructor
        ~bshipboard(); // destructor

        void populateboard();
        void displayfullboard();
        bool done();
        int checkturn();
        int domove(std::vector<int> move);
};



#endif