#include "piece.h"
#include "board.h"
using namespace std;

Piece::Piece(int r, int c, Board& b, bool isWhite): row{r}, col{c}, b{b}, isWhite{isWhite}, unmoved{true} {}
bool Piece::isWhitePiece(){return isWhite;};
void Piece::moved() { unmoved = false; }
void Piece::setPosition(int newRow, int newCol) { row = newRow; col = newCol; }
bool Piece::isUnmoved() const { return unmoved; }

Pawn::Pawn(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Pawn::validMoves() const {
  vector<pair<int, int>> moves;
  Move lastMove = b.prevMoves.empty() ? Move{{-1,-1},{-1,-1}} : b.prevMoves.top();

  // check if last move was by a pawn and it moved two squares
  bool pawnDoubleMovedLast =
    !b.prevMoves.empty() &&
    tolower(
      b.at(lastMove.end.first, lastMove.end.second)
      ->getSymbol()
    ) == 'p' && 
    abs(lastMove.start.first - lastMove.end.first) == 2
  ;

  if (isWhite) {
    if (row-1 >= 0 && b.at(row-1, col) == nullptr) moves.emplace_back(row-1, col);
    if (unmoved && row-1 >= 0 && b.at(row-1, col) == nullptr && row-2 >= 0 && b.at(row-2, col) == nullptr) moves.emplace_back(row-2, col);
    if (row-1 >= 0 && col-1 >= 0 && b.at(row-1, col-1) != nullptr && !b.at(row-1, col-1)->isWhitePiece()) moves.emplace_back(row-1, col-1);
    if (row-1 >= 0 && col+1 <= 7 && b.at(row-1, col+1) != nullptr && !b.at(row-1, col+1)->isWhitePiece()) moves.emplace_back(row-1, col+1);
    
    // en passant
    if (pawnDoubleMovedLast) {
      int r = row;
      if (lastMove.end == make_pair(r, col+1) && !b.at(row, col+1)->isWhitePiece()) moves.emplace_back(row-1, col+1);
      if (lastMove.end == make_pair(r, col-1) && !b.at(row, col-1)->isWhitePiece()) moves.emplace_back(row-1, col-1);
    }
  }
  else {
    if (row+1 <= 7 && b.at(row+1, col) == nullptr) moves.emplace_back(row+1, col);
    if (unmoved && row+1 <= 7 && b.at(row+1, col) == nullptr && row+2 <= 7 && b.at(row+2, col) == nullptr) moves.emplace_back(row+2, col);
    if (row+1 <= 7 && col-1 >= 0 && b.at(row+1, col-1) != nullptr && b.at(row+1, col-1)->isWhitePiece()) moves.emplace_back(row+1, col-1);
    if (row+1 <= 7 && col+1 <= 7 && b.at(row+1, col+1) != nullptr && b.at(row+1, col+1)->isWhitePiece()) moves.emplace_back(row+1, col+1);
    
    // en passant
    if (pawnDoubleMovedLast) {
      int r = row;
      if (lastMove.end == make_pair(r, col+1) && b.at(row, col+1)->isWhitePiece()) moves.emplace_back(row+1, col+1);
      if (lastMove.end == make_pair(r, col-1) && b.at(row, col-1)->isWhitePiece()) moves.emplace_back(row+1, col-1);
    }
  }

  return moves;
}
char Pawn::getSymbol() const { return isWhite ? 'P' : 'p'; }

King::King(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite}, canCastle{true} {}
vector<pair<int, int>> King::validMoves() const {
  vector<pair<int, int>> moves;
  for (int r = -1; r <= 1; ++r) {
    int newRow = row+r;
    for (int c = -1; c <= 1; ++c) {
      int newCol = col+c;
      if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7) {
        moves.emplace_back(newRow, newCol);
      }
    }
  }
  if (canCastle && unmoved) {
    if (b.at(row, 0) != nullptr && col-2 >= 0){
      if(tolower(b.at(row, 0)->getSymbol()) == 'r') {
      bool flag = true;
      for (int i = 1; i < col ; ++i) {
        if (b.at(row, i) != nullptr) {
          flag = false;
          break;
        }
      }
      // all spaces between are empty: castling is a valid move
      if (flag && col-2 >= 0 && b.at(row, 0)->isUnmoved()) moves.emplace_back(row, col-2);
    }}

    if (b.at(row, 7) != nullptr && col + 2 <= 7) {
      if(tolower(b.at(row, 7)->getSymbol()) == 'r') {
      bool flag = true;
      for (int i = 6; i > col ; --i) {
        if (b.at(row, i) != nullptr) {
          flag = false;
          break;
        }
      }
      // all spaces between are empty: castling is a valid move
      if (flag && col+2 <= 7 &&b.at(row, 7)->isUnmoved()){
         moves.emplace_back(row, col+2);}
    }
    }
  }

  return moves;
}
char King::getSymbol() const { return isWhite ? 'K' : 'k'; }



Bishop::Bishop(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Bishop::validMoves() const {
  vector<pair<int, int>> moves;

  // while loops that go diagonally in each direction on the Game until its out of bounds
  int r = row, c = col;
  while (++r <= 7 && ++c <= 7) {
    moves.emplace_back(r, c);
    if (b.at(r,c) != nullptr) break;
  }
  r = row; c = col;
  while (--r >= 0 && --c >= 0) {
    moves.emplace_back(r, c);
    if (b.at(r,c) != nullptr) break;
  }
  r = row; c = col;
  while (++r <= 7 && --c >= 0) {
    moves.emplace_back(r, c);
    if (b.at(r,c) != nullptr) break;
  }
  r = row; c = col;
  while (--r >= 7 && ++c <= 7) {
    moves.emplace_back(r, c);
    if (b.at(r,c) != nullptr) break;
  }

  return moves;
}
char Bishop::getSymbol() const { return isWhite ? 'B' : 'b'; }

Rook::Rook(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Rook::validMoves() const {
    vector<pair<int, int>> moves;

    // add all valid horizontal moves
    for (int c = col + 1; c <= 7; c++) {
        moves.emplace_back(row, c);
        if (b.at(row, c) != nullptr) break;
    }
    for (int c = col - 1; c >= 0; c--) {
        moves.emplace_back(row, c);
        if (b.at(row, c) != nullptr) break;
    }
    // add all valid vertical moves
    for (int r = row + 1; r <= 7; r++) {
        moves.emplace_back(r, col);
        if (b.at(r, col) != nullptr) break;
    }
    for (int r = row - 1; r >= 0; r--) {
        moves.emplace_back(r, col);
        if (b.at(r, col) != nullptr) break;
    }

    return moves;
}
char Rook::getSymbol() const { return isWhite ? 'R' : 'r'; }

Queen::Queen(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Queen::validMoves() const {
  // a Queen can move like a Rook or Bishop
  // so, we'll instantiate a Rook and Bishop at the same coords as the Queen and find their possible moves
  Rook r{row, col, b, isWhite};
  Bishop bish{row, col, b, isWhite};

  vector<pair<int, int>> rookMoves = r.validMoves();
  vector<pair<int, int>> bishopMoves = bish.validMoves();
  
  // merge all possible moves into one vector
  vector<pair<int, int>> mergedMoves(rookMoves.size() + bishopMoves.size());
  mergedMoves.insert(mergedMoves.end(), rookMoves.begin(), rookMoves.end());
  mergedMoves.insert(mergedMoves.end(), bishopMoves.begin(), bishopMoves.end());
  
  return mergedMoves;
}
char Queen::getSymbol() const { return isWhite ? 'Q' : 'q'; }

Knight::Knight(int r, int c, Board& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Knight::validMoves() const {
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
char Knight::getSymbol() const { return isWhite ? 'N' : 'n'; }
