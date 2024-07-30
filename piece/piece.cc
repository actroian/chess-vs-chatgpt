#include "piece.h"
#include "board.h"
#include "move.h"
#include "globals.h"

using namespace std;

Piece::Piece(int r, int c, Board& b, bool isWhite): row{r}, col{c}, b{b}, isWhite{isWhite}, unmoved{true} {}
bool Piece::isWhitePiece(){return isWhite;}
void Piece::setUnmoved(bool isUnmoved) { unmoved = isUnmoved; }
void Piece::setPosition(int newRow, int newCol) { row = newRow; col = newCol; }
bool Piece::isUnmoved() const { return unmoved; }
