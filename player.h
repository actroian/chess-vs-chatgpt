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
    
  public:
    Player(bool);
    virtual bool move(unique_ptr<Board>& b, const pair<int, int>&, const pair<int, int>&) = 0; 
    vector<Move> possibleMoves(unique_ptr<Board>& board);
    vector<pair<int, int>> outOfCheckMoves();
    bool isInCheck() const;
    void setInCheck(bool);
    void setPieces(vector<unique_ptr<Piece>&>);
    bool isP1();
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    bool move(unique_ptr<Board>& b, const pair<int, int>&, const pair<int, int>&) override;  
};

#endif
