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
    std::unique_ptr<Move> checkCastle(std::unique_ptr<Board>& b, const std::pair<int,int>& start, const std::pair<int,int>& end);
    
  public:
    Player(bool);
    virtual Move chooseMove(std::unique_ptr<Board>& b) = 0;
    bool move(std::unique_ptr<Board>& b); 
    std::vector<Move> possibleMoves(std::unique_ptr<Board>& board);
    std::vector<std::pair<int, int>> outOfCheckMoves();
    bool isInCheck() const;
    void setInCheck(bool);
    void setPieces(std::vector<std::unique_ptr<Piece>&>);
    bool isP1();
    bool kingInCheck(std::unique_ptr<Board>& b, std::unique_ptr<Player>& p2 ) const;
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    Move chooseMove(std::unique_ptr<Board>& b) override;
};

#endif
