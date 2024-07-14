#ifndef PLAYER_H
#define PLAYER_H

class Player {
  protected:
    bool white;
    bool inCheck;
  public:
    Player(bool);
    bool isWhite();
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
    void resign();
};

class Computer: public Player {
  public:
    Computer(bool);
};

#endif
