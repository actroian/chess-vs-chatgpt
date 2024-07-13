#include "piece.h"
#include "game.h"
using namespace std;

// TODO: fix valid moves so it adds a valid move on the first instance
// of the square it can go to has an opposite colored piece

Piece::Piece(int r, int c, Game& b, bool isWhite): row{r}, col{c}, b{b}, isWhite{isWhite} {}

Pawn::Pawn(int r, int c, Game& b, bool isWhite): Piece{r, c, b, isWhite}, unmoved{true} {}
vector<pair<int, int>> Pawn::validMoves() const {
  vector<pair<int, int>> moves;

  if (isWhite) {
    if (row-1 >= 0 && b.board[row-1][col] == nullptr) moves.emplace_back(row-1, col);
    if (unmoved && row-2 >= 0 && b.board[row-2][col] == nullptr) moves.emplace_back(row-2, col);
    // TODO: en passant
  }
  else {
    if (row+1 <= 7 && b.board[row+1][col] == nullptr) moves.emplace_back(row+1, col);
    if (unmoved && row+2 <= 7 && b.board[row+2][col] == nullptr) moves.emplace_back(row+2, col);
    // TODO: en passant
  }

  return moves;
}
char Pawn::getSymbol() const { return isWhite ? 'P' : 'p'; }

King::King(int r, int c, Game& b, bool isWhite): Piece{r, c, b, isWhite}, canCastle{true} {}
vector<pair<int, int>> King::validMoves() const {
  vector<pair<int, int>> moves;
  for (int r = -1; r <= 1; ++r) {
    int newRow = row+r;
    for (int c = -1; c <= 1; ++c) {
      int newCol = col+c;
      if (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7 && b.board[newRow][newCol] == nullptr) {
        moves.emplace_back(newRow, newCol);
      }
    }
  }
  if (canCastle) {
    // TODO: push back some move - need to which rook(s) can be castled with too
    if (b.board[row][0]->getSymbol() == (isWhite ? 'R' : 'r')) {
      bool flag = true;
      for (int i = 1; i < col ; ++i) {
        if (b.board[row][i] != nullptr) {
          flag = false;
          break;
        }
      }
      // all spaces between are empty: castling is a valid move
      if (flag && col-2 >= 0) moves.emplace_back(row, col-2);
    }
    if (b.board[row][7]->getSymbol() == (isWhite ? 'R' : 'r')) {
      bool flag = true;
      for (int i = 6; i > col ; --i) {
        if (b.board[row][i] != nullptr) {
          flag = false;
          break;
        }
      }
      // all spaces between are empty: castling is a valid move
      if (flag && col+2 <= 7) moves.emplace_back(row, col+2);
    }
  }

  return moves;
}
char King::getSymbol() const { return isWhite ? 'K' : 'k'; }



Bishop::Bishop(int r, int c, Game& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Bishop::validMoves() const {
  vector<pair<int, int>> moves;

  // while loops that go diagonally in each direction on the Game until its out of bounds
  int r = row, c = col;
  while (++r <= 7 && ++c <= 7) {
    if (b.board[r][c] != nullptr) break;
    moves.emplace_back(r, c);
  }
  r = row; c = col;
  while (--r >= 0 && --c >= 0) {
    if (b.board[r][c] != nullptr) break;
    moves.emplace_back(r, c);
  }
  r = row; c = col;
  while (++r <= 7 && --c >= 0) {
    if (b.board[r][c] != nullptr) break;
    moves.emplace_back(r, c);
  }
  r = row; c = col;
  while (--r >= 7 && ++c <= 7) {
    if (b.board[r][c] != nullptr) break;
    moves.emplace_back(r, c);
  }

  return moves;
}
char Bishop::getSymbol() const { return isWhite ? 'B' : 'b'; }

Rook::Rook(int r, int c, Game& b, bool isWhite): Piece{r, c, b, isWhite}, unmoved{true} {}
vector<pair<int, int>> Rook::validMoves() const {
  vector<pair<int, int>> moves;

  // add all valid horizontal moves
  for (int c = col+1; c <= 7; ++c) {
    if (b.board[row][c] != nullptr) break;
    moves.emplace_back(row, c);
  }
  for (int c = col-1; c >= 0; --c) {
    if (b.board[row][c] != nullptr) break;
    moves.emplace_back(row, c);
  }
  // add all valid vertical moves
  for (int r = row+1; r <= 7; ++r) {
    if (b.board[r][col] != nullptr) break;
    moves.emplace_back(r, col);
  }
  for (int r = row-1; r >= 0; --r) {
    if (b.board[r][col] != nullptr) break;
    moves.emplace_back(r, col);
  }

  return moves;
}
char Rook::getSymbol() const { return isWhite ? 'R' : 'r'; }

Queen::Queen(int r, int c, Game& b, bool isWhite): Piece{r, c, b, isWhite} {}
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

Knight::Knight(int r, int c, Game& b, bool isWhite): Piece{r, c, b, isWhite} {}
vector<pair<int, int>> Knight::validMoves() const {
  vector<pair<int, int>> moves;

  if (row+1 <= 7 && col+2 <= 7 && b.board[row+1][col+2] == nullptr) moves.emplace_back(row+1, col+2);
  if (row+2 <= 7 && col+1 <= 7 && b.board[row+2][col+1] == nullptr) moves.emplace_back(row+2, col+1);
  if (row+1 <= 7 && col-2 >= 0 && b.board[row+1][col-2] == nullptr) moves.emplace_back(row+1, col-2);
  if (row+2 <= 7 && col-1 >= 0 && b.board[row+2][col-1] == nullptr) moves.emplace_back(row+2, col-1);
  if (row-1 >= 0 && col+2 <= 7 && b.board[row-1][col+2] == nullptr) moves.emplace_back(row-1, col+2);
  if (row-2 >= 0 && col+1 <= 7 && b.board[row-2][col+1] == nullptr) moves.emplace_back(row-2, col+1);
  if (row-1 >= 0 && col-2 >= 0 && b.board[row-1][col-2] == nullptr) moves.emplace_back(row-1, col-2);
  if (row-2 >= 0 && col-1 >= 0 && b.board[row-2][col-1] == nullptr) moves.emplace_back(row-2, col-1);

  return moves;
}
char Knight::getSymbol() const { return isWhite ? 'N' : 'n'; }
