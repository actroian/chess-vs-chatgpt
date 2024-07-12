#include <vector>
#include <utility>
class Board;

class Piece {
  protected:
    int row, col;
    //Board& b;
  public:
    Piece(int, int/*, Board&*/);
    virtual std::vector<std::pair<int, int>> possibleMoves() const = 0;
    virtual char getSymbol() const = 0;
    virtual ~Piece() {}
};

class Pawn: public Piece {
    bool unmoved;
    void promote();
  public:
    Pawn(int, int);
    std::vector<std::pair<int, int>> possibleMoves() const override;
    char getSymbol() const override;
};
class King: public Piece {
    bool canCastle;
  public:
    King(int, int);
    std::vector<std::pair<int, int>> possibleMoves() const override;
    char getSymbol() const override;
};
class Bishop: public Piece {
  public:
    Bishop(int, int);
    std::vector<std::pair<int, int>> possibleMoves() const override;
    char getSymbol() const override;
};
class Rook: public Piece {
  public:
    Rook(int, int);
    std::vector<std::pair<int, int>> possibleMoves() const override;
    char getSymbol() const override;
};
class Queen: public Piece {
  public:
    Queen(int, int);
    std::vector<std::pair<int, int>> possibleMoves() const override;
    char getSymbol() const override;
};
class Knight: public Piece {
  public:
    Knight(int, int);
    std::vector<std::pair<int, int>> possibleMoves() const override;
    char getSymbol() const override;
};
