#include "Player.h"

Player::Player()
{
    user = -1;
    type = PLAYER_TYPE_NONE;
}

Player::Player(int user)
{
    setUser(user);
    setPlayerType(PLAYER_TYPE_NONE);
}

Player::Player(int user, PlayerType type)
{
    setPlayerType(type);
    setUser(user);
}

PlayerType Player::getPlayerType() const
{
    return type;
}

void Player::setPlayerType(PlayerType type)
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
