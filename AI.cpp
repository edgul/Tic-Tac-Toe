#include "AI.h"

AI::AI()
{

}

// Assumes AI never asked to make a move when no moves left to make
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
