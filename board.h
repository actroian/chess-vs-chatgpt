#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>

#include "piece.h"
#include "globals.h"
#include "player.h"

class Player;

class Board{
  std::vector<std::vector<std::unique_ptr<Piece>>> board;
  bool p1Turn, custom;
    
  public:
    Board();
    void setup();
    void resetBoard(std::unique_ptr<Player>& p1, std::unique_ptr<Player>& p2);
    void print(std::ostream&) const;
    void placePiece(int, int, std::unique_ptr<Piece>&&);
    void removePiece(int, int);
    std::unique_ptr<Piece>& at(int, int);
    bool isP1Turn() const;
    bool isCustom() const;
    void setP1Turn(bool);
    void clearBoard();
};

#endif