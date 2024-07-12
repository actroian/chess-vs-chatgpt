#ifndef PLAYER_H
#define PLAYER_H

class Player {
  protected:
    bool white;
  public:
    bool isWhite();
};

class Human: public Player {

};

class Computer: public Player {

};

class L1: public Computer {

};
class L2: public Computer {

};

class L3: public Computer {

};

#endif
