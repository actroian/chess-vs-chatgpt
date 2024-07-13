#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>
class Game;

class Piece {
  protected:
    int row, col;
    Game& b;
    bool isWhite;
  public:
    Piece(int, int, Game&, bool);
    virtual std::vector<std::pair<int, int>> validMoves() const = 0;
    virtual char getSymbol() const = 0;
    virtual ~Piece() {}
};

class Pawn: public Piece {
    bool unmoved;
    void promote();
  public:
    Pawn(int, int, Game&, bool);
    std::vector<std::pair<int, int>> validMoves() const override;
    char getSymbol() const override;
};
class King: public Piece {
    bool canCastle;
  public:
    King(int, int, Game&, bool);
    std::vector<std::pair<int, int>> validMoves() const override;
    char getSymbol() const override;
};
class Bishop: public Piece {
  public:
    Bishop(int, int, Game&, bool);
    std::vector<std::pair<int, int>> validMoves() const override;
    char getSymbol() const override;
};
class Rook: public Piece {
    bool unmoved;
  public:
    Rook(int, int, Game&, bool);
    std::vector<std::pair<int, int>> validMoves() const override;
    char getSymbol() const override;
};
class Queen: public Piece {
  public:
    Queen(int, int, Game&, bool);
    std::vector<std::pair<int, int>> validMoves() const override;
    char getSymbol() const override;
};
class Knight: public Piece {
  public:
    Knight(int, int, Game&, bool);
    std::vector<std::pair<int, int>> validMoves() const override;
    char getSymbol() const override;
};

#endif
