#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <string>
#include "move.h"
#include "board.h"
class Piece;

class Player {
  protected:
    bool isWhite;
    bool inCheck;
    
  public:
    Player(bool);
    virtual bool move(std::unique_ptr<Board>& b, const std::pair<int, int>&, const std::pair<int, int>&) = 0; 
    std::vector<Move> possibleMoves(std::unique_ptr<Board>& board);
    std::vector<std::pair<int, int>> outOfCheckMoves();
    bool isInCheck() const;
    void setInCheck(bool);
    void setPieces(std::vector<std::unique_ptr<Piece>&>);
    bool isP1();
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    bool move(std::unique_ptr<Board>& b, const std::pair<int, int>&, const std::pair<int, int>&) override;  
};

#endif
