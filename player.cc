#include "player.h"
using namespace std;

Player::Player(bool isWhite): white{isWhite}, inCheck{false} {}
Player::~Player() {}
bool Player::isWhite() { return white; }

Human::Human(bool isWhite): Player{isWhite} {}

Computer::Computer(bool isWhite): Player{isWhite} {}
