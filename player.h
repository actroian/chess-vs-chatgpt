#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "board.h"
#include "move.h"
using namespace std;
class Move;

class Player {
  protected:
    bool isWhite;
    bool inCheck;
    vector<Move> possibleMoves(unique_ptr<Board>& board);

  public:
    Player(bool);
    virtual bool move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) = 0; 
    bool isInCheck() const;
    vector<pair<int, int>> outOfCheckMoves();
    void setPieces(vector<unique_ptr<Piece>&>);
    bool isP1();
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    bool move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) override;  
};

class Computer: public Player {
  public:
    Computer(bool);
    virtual pair<pair<int, int>, pair<int, int>> chooseMove() = 0;
};

class L1: public Computer {
  public:
    L1(bool);
    bool move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) override;
    pair<pair<int, int>, pair<int, int>> chooseMove() override;
    vector<pair<int, int>> getAllMoves();
};

class L2: public L1 {
  public:
    L2(bool);
    bool move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) override;
    pair<pair<int, int>, pair<int, int>> chooseMove() override;
    vector<pair<int, int>> captureMoves();
    vector<pair<int, int>> checkMoves();
};

class L3: public L2 {
  public:
    L3(bool);
    bool move(unique_ptr<Board>& b, int startrow, int startcol, int endrow, int endcol) override;
    pair<pair<int, int>, pair<int, int>> chooseMove() override;
    vector<pair<int, int>> checkmateMoves();
    vector<pair<int, int>> avoidCaptureMoves();
};
#endif
