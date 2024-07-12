#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <memory>
#include "player.h"
class Piece;

class Game {
    std::ostream& out;
    int wScore, bScore;
    Player& p1, &p2;

  public:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    Game(std::ostream&, Player&, Player&);
    void print() const;
    void reset();
    void setup();
};

#endif