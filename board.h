#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>

#include "globals.h"
#include "move.h"
#include "piece.h"

class Player;

class Board{
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    bool p1Turn, custom;
    Move lastMove;
  public:
    Board();
    void setup();
    void resetBoard(std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2);
    void print(std::ostream&) const;
    void placePiece(int, int, std::unique_ptr<Piece>&&);
    void removePiece(int, int);
    std::unique_ptr<Piece>& at(int, int);
    std::unique_ptr<Piece> createPiece(std::string&, const std::pair<int,int>&) const;
    bool isP1Turn() const;
    bool isCustom() const;
    bool moveable(bool, const std::pair<int,int>&) const;
    void setP1Turn(bool);
    void setLastMove(const Move&);
    Move getLastMove() const;
    void clearBoard();
};

#endif