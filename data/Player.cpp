#include "Player.h"

Player::Player() : Player(-1, PIECE_TYPE_NONE)
{
}


Player::Player(int user, PieceType type) :
    type_(type),
    user_(user)
{
}

PieceType Player::getPieceType() const
{
    return type_;
}

void Player::setPlayerType(PieceType type)
{
    type_ = type;
}

void Player::setUser(int user)
{
    user_ = user;
}

int Player::getUser() const
{
    return user_;
}

bool operator==(const Player& lhs, const Player& rhs)
{
    return lhs.getUser() == rhs.getUser();
}
