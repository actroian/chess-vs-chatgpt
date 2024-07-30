#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cctype>
#include <algorithm>
#include <memory>
#include <map>
#include "player.h"
#include "human.h"
#include "normalmove.h"
#include "enpassantmove.h"
#include "castlemove.h"
#include "promotionmove.h"
#include "L1.h"
#include "L2.h"
#include "L3.h"
#include "L4.h"

class Player;
class Board;

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
    void printScore(bool = false) const;
    bool initiateMove();
    void print(bool = true);
    void updateState(bool setupMode = false);
    void reset();
    void setup();
    void endGame(int, bool = false);
    void beginGame(const std::string&, const std::string&);
    bool move(unique_ptr<Board>& b, unique_ptr<Player>& moving_player, unique_ptr<Player>& opponent);
};

#endif
