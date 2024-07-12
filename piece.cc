#include "piece.h"
using namespace std;

Piece::Piece(int r, int c): row{r}, col{c} {}

Pawn::Pawn(int r, int c): Piece{r, c}, unmoved{true} {}
vector<pair<int, int>> Pawn::possibleMoves() const {
  vector<pair<int, int>> moves;
  // TODO: how to differentiate between white/black piece moving up/down?
  // this implementation is for a white piece only
  if (row-1 >= 0) moves.emplace_back(row-1, col);
  if (unmoved) moves.emplace_back(row-2, col);
  return moves;
}
char Pawn::getSymbol() const { return 'P'; }

King::King(int r, int c): Piece{r, c}, canCastle{true} {}
vector<pair<int, int>> King::possibleMoves() const {
  vector<pair<int, int>> moves;
  for (int r = -1; r <= 1; ++r) {
    int newRow = row+r;
    for (int c = -1; c <= 1; ++c) {
      int newCol = col+c;
      if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7 && !(r == 0 && c == 0)) {
        moves.emplace_back(newRow, newCol);
      }
    }
  }
  if (canCastle) {
    // TODO: push back some move - need to which rook(s) can be castled with too 
  }

  return moves;
}
char King::getSymbol() const { return 'K'; }



Bishop::Bishop(int r, int c): Piece{r, c} {}
vector<pair<int, int>> Bishop::possibleMoves() const {
  vector<pair<int, int>> moves;

  // while loops that go diagonally in each direction on the board until its out of bounds
  int r = row, c = col;
  while (++r <= 7 && ++c <= 7) {
    moves.emplace_back(r, c);
  }
  r = row; c = col;
  while (--r >= 0 && --c >= 0) {
    moves.emplace_back(r, c);
  }
  r = row; c = col;
  while (++r <= 7 && --c >= 0) {
    moves.emplace_back(r, c);
  }
  r = row; c = col;
  while (--r >= 7 && ++c <= 7) {
    moves.emplace_back(r, c);
  }

  return moves;
}
char Bishop::getSymbol() const { return 'B'; }

Rook::Rook(int r, int c): Piece{r, c} {}
vector<pair<int, int>> Rook::possibleMoves() const {
  vector<pair<int, int>> moves;

  for (int pos = 0; pos <= 7; ++pos) {
    if (pos != col) {
      moves.emplace_back(row, pos);
    }
    if (pos != row) {
      moves.emplace_back(pos, col);
    }
  }

  return moves;
}
char Rook::getSymbol() const { return 'R'; }

Queen::Queen(int r, int c): Piece{r, c} {}
vector<pair<int, int>> Queen::possibleMoves() const {
  // a Queen can move like a Rook or Bishop
  // so, we'll instantiate a Rook and Bishop at the same coords as the Queen and find their possible moves
  Rook r{row, col};
  Bishop b{row, col};

  vector<pair<int, int>> rookMoves = r.possibleMoves();
  vector<pair<int, int>> bishopMoves = b.possibleMoves();
  
  // merge all possible moves into one vector
  vector<pair<int, int>> mergedMoves(rookMoves.size() + bishopMoves.size());
  mergedMoves.insert(mergedMoves.end(), rookMoves.begin(), rookMoves.end());
  mergedMoves.insert(mergedMoves.end(), bishopMoves.begin(), bishopMoves.end());
  
  return mergedMoves;
}
char Queen::getSymbol() const { return 'Q'; }

Knight::Knight(int r, int c): Piece{r, c} {}
vector<pair<int, int>> Knight::possibleMoves() const {
  vector<pair<int, int>> moves;

  if (row+1 <= 7 && col+2 <= 7) moves.emplace_back(row+1, col+2);
  if (row+2 <= 7 && col+1 <= 7) moves.emplace_back(row+2, col+1);
  if (row+1 <= 7 && col-2 >= 0) moves.emplace_back(row+1, col-2);
  if (row+2 <= 7 && col-1 >= 0) moves.emplace_back(row+2, col-1);
  if (row-1 >= 0 && col+2 <= 7) moves.emplace_back(row-1, col+2);
  if (row-2 >= 0 && col+1 <= 7) moves.emplace_back(row-2, col+1);
  if (row-1 >= 0 && col-2 >= 0) moves.emplace_back(row-1, col-2);
  if (row-2 >= 0 && col-1 >= 0) moves.emplace_back(row-2, col-1);

  return moves;
}
char Knight::getSymbol() const { return 'N'; }
