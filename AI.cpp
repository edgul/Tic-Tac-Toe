#include "AI.h"

AI::AI()
{

}

// Assumes there is at least one move to make
Quad AI::get_move(Board board)
{
    Quad move;

    // dumb AI -- first empty quad
    for (int i = 0; i < board.size(); i ++)
    {
        if (board.piece_at(i) == "")
        {
            move = (Quad) i;
            break;
        }
    }

    return move;
}
