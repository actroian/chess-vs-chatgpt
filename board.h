#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <memory>

#include "piece.h"
#include "globals.h"

class Board{
  std::vector<std::vector<std::unique_ptr<Piece>>> board;
  Game& game; //a reference to the game
    
  public:
    Board(Game& game);
    std::unique_ptr<Piece>& at(int row, int col);
    void resetBoard();
    void print(std::ostream& out) const;
    void placePiece(int row, int col, std::unique_ptr<Piece> piece);
    void removePiece(int row, int col);
};

#endif