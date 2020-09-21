#ifndef PLAYER_H
#define PLAYER_H

#include "data.h"

class Player
{
public:
    Player();
    Player(int user_, PieceType type_);

    PieceType getPieceType() const;
    void setPlayerType(PieceType type_);

    void setUser(int user_);
    int getUser() const;

    friend bool operator==(const Player& lhs, const Player& rhs);

private:
    PieceType type_;
    int user_;
};



#endif // PLAYER_H
