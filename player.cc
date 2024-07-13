#include "player.h"

Player::Player(bool isWhite): white{isWhite} {}
Player::~Player() {}
bool Player::isWhite() { return white; }

Human::Human(bool isWhite): Player{isWhite} {}

Computer::Computer(bool isWhite): Player{isWhite} {}
