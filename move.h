#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <utility>

class Move {
  public:
    std::pair<int, int> start;
    std::pair<int, int> end;

    Move(std::pair<int, int>, std::pair<int, int>);
    Move getMove() const;
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;
    ~Move() {}
};

#endif
