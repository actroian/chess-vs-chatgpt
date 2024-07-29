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
    bool isBot;
    std::unique_ptr<Move> checkCastle(std::unique_ptr<Board>& b, const std::pair<int,int>& start, const std::pair<int,int>& end);
    std::vector<Move> getOtherPlayersMoves(std::unique_ptr<Board>& b);

  public:
    Player(bool, bool = true);
    virtual std::unique_ptr<Move> chooseMove(std::unique_ptr<Board>& b, Player* p2) = 0;
    std::vector<std::unique_ptr<Move>> possibleMoves( std::unique_ptr<Board>& board, Player* p2, bool checkTest = true) ;
    std::vector<std::pair<int, int>> outOfCheckMoves();
    bool isInCheck() const;
    bool isABot() const;
    void setInCheck(bool);
    void setPieces(std::vector<std::unique_ptr<Piece>&>);
    bool isP1();
    bool kingInCheck(std::unique_ptr<Board>& b, Player* p1, Player* p2 ) ;
    std::vector<std::pair<int, int>> getMyPiecePositions(std::unique_ptr<Board>& b, bool isWhite);
    std::vector<std::unique_ptr<Move>> allMoves(std::unique_ptr<Board>& board, Player* p2);
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    std::unique_ptr<Move> chooseMove(std::unique_ptr<Board>& b, Player* p2) override;
};

#endif
