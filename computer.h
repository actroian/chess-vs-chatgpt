#ifndef COMPUTER_H
#define COMPUTER_H
#include "move.h"
#include "player.h"

using namespace std;

class Player;

class Computer: public Player {
  public:
    Computer(bool isWhite) : Player(isWhite) {}
    virtual pair<pair<int, int>, pair<int, int>> chooseMove() = 0;
};


#endif
