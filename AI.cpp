#include "AI.h"

AI::AI()
{

}

// Assumes there is at least one move to make
Quad AI::get_move(QList<QString> board)
{
    Quad move;

    // dumb AI -- first empty quad
    for (int i = 0; i < board.length(); i ++)
    {
        if (board[i] == "")
        {
            move = (Quad) i;
            break;
        }
    }

    return move;
}
