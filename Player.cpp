#include "Player.h"

Player::Player()
{
    user = -1;
    type = PIECE_TYPE_NONE;
}

Player::Player(int user)
{
    setUser(user);
    setPlayerType(PIECE_TYPE_NONE);
}

Player::Player(int user, PieceType type)
{
    setPlayerType(type);
    setUser(user);
}

PieceType Player::getPieceType() const
{
    return type;
}

void Player::setPlayerType(PieceType type)
{
    this->type = type;
}

void Player::setUser(int user)
{
    this->user = user;
}

int Player::getUser() const
{
    return user;
}

bool operator==(const Player& lhs, const Player& rhs)
{
    return lhs.getUser() == rhs.getUser();
}
