#include <iostream>
#include <vector>
#include <utility>
#include "piece.h"

class Chessboard {
    std::ostream& out;
  // we can change to all private fields/methods if this becomes a nested class in Game
  public:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    Chessboard(std::ostream&, bool);
    void setup();
    void print() const;
};
