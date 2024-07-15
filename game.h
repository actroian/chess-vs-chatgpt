#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cctype>
#include <algorithm>
#include <memory>
#include <map>
#include "player.h"
#include "piece.h"

class Game {
    std::ostream& out;
    double wScore, bScore;
    bool p1Turn;
  public:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    std::unique_ptr<Player> p1, p2;
    Game();
    Game(std::ostream&, std::unique_ptr<Player>, std::unique_ptr<Player>);
    bool isP1Turn() const;
    void print() const;
    void reset();
    void setup();
    void endGame(int);
};

#endif