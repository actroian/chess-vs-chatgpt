#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cctype>
#include <algorithm>
#include <memory>
#include <map>
#include "player.h"
#include "piece.h"
#include "board.h"

class Game {
    std::ostream& out;
    double wScore, bScore;
    bool inGame;

    const std::string HUMAN = "human";
    const std::string COMPUTER = "computer";
    const std::string L1input = "computer1";
    const std::string L2input = "computer2";
    const std::string L3input = "computer3";
    const std::string L4input = "computer4";
    std::unique_ptr<Player> createPlayer(const std::string&, bool);
  public:
    std::unique_ptr<Board> board;
    std::unique_ptr<Player> p1, p2;
    Game();
    bool isInGame() const;
    void print() const;
    void move(pair<int, int> start, pair<int, int> end);
    void reset();
    void endGame(int);
    void beginGame(const std::string&, const std::string&);
};

#endif