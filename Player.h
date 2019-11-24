#ifndef PLAYER_H
#define PLAYER_H

enum PlayerType
{
    PLAYER_TYPE_NONE,
    PLAYER_TYPE_X,
    PLAYER_TYPE_O
};

class Player
{
public:
    Player();
    Player(int user);
    Player(int user, PlayerType type);

    PlayerType getPlayerType() const;
    void setPlayerType(PlayerType type);

    void setUser(int user);
    int getUser() const;

    friend bool operator==(const Player& lhs, const Player& rhs);

private:
    PlayerType type;

    int user;
};



#endif // PLAYER_H
