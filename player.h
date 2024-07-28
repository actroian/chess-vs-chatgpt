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
    virtual Move chooseMove(std::unique_ptr<Board>& b) = 0;
    bool move(std::unique_ptr<Board>& b, std::unique_ptr<Player>& p2);
    bool castle(std::unique_ptr<Board>& b, std::unique_ptr<Player>& p2, Move move, std::unique_ptr<Move>& castle_move);
    std::vector<Move> possibleMoves(const std::unique_ptr<Board>& board);
    std::vector<std::pair<int, int>> outOfCheckMoves();
    bool isInCheck() const;
    bool isABot() const;
    void setInCheck(bool);
    void setPieces(std::vector<std::unique_ptr<Piece>&>);
    bool isP1();
    bool kingInCheck(std::unique_ptr<Board>& b, std::unique_ptr<Player>& p2 ) const;
    std::vector<std::pair<int, int>> getMyPiecePositions(std::unique_ptr<Board>& b, bool isWhite);
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    Move chooseMove(std::unique_ptr<Board>& b) override;
};

#endif
