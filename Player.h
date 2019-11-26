#ifndef PLAYER_H
#define PLAYER_H

#include "data.h"

class Player
{
public:
    Player();
    Player(int user);
    Player(int user, PieceType type);

    PieceType getPieceType() const;
    void setPlayerType(PieceType type);

    void setUser(int user);
    int getUser() const;

    friend bool operator==(const Player& lhs, const Player& rhs);

private:
    PieceType type;
    int user;
};



#endif // PLAYER_H
