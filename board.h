#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>

#include "piece.h"
#include "globals.h"

class Board{
  std::vector<std::vector<std::unique_ptr<Piece>>> board;
  bool p1Turn, custom;
    
  public:
    Board();
    void setup();
    void resetBoard();
    void print(std::ostream&) const;
    void placePiece(int, int, std::unique_ptr<Piece>&&);
    void removePiece(int, int);
    const std::unique_ptr<Piece>& at(int, int) const;
    bool isP1Turn() const;
    bool isCustom() const;
    void setP1Turn(bool);
    void clearBoard();
};

#endif