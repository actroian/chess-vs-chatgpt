#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>
#include <stack>

#include "globals.h"
#include "move.h"
#include "piece.h"

class Player;

class Board{
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    bool p1Turn, custom;
    
    bool validateBoard();
    void undo();
  public:
    std::stack<Move> prevMoves;

    Board();
    void setup();
    void resetBoard();
    void print(std::ostream&) const;
    void placePiece(int, int, std::unique_ptr<Piece>&&);
    void removePiece(int, int);
    std::unique_ptr<Piece>& at(int, int);
    std::unique_ptr<Piece> createPiece(std::string&, const std::pair<int,int>&) const;
    bool isP1Turn() const;
    bool isCustom() const;
    bool moveable(bool, const std::pair<int,int>&) const;
    void setP1Turn(bool);
    void clearBoard();
};

#endif