#ifndef PLAYER_H
#define PLAYER_H

class Player {
  protected:
    bool white;
  public:
    Player(bool);
    bool isWhite();
    virtual ~Player() = 0;
};

class Human: public Player {
  public:
    Human(bool);
};

class Computer: public Player {
  public:
    Computer(bool);
};

#endif
