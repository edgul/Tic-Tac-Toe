#include "AI.h"

AI::AI()
{

}

Quad AI::get_move(Board board)
{
    // ai actually goes
    Quad best_move = board.available_win(piece_type);

    if (best_move == QUAD_NONE)
    {
        QString player_piece = PLAYER_O;
        if (piece_type == PLAYER_O) player_piece = PLAYER_X;

        best_move = board.available_win(player_piece);
    }

    if (best_move == QUAD_NONE)
    {
        best_move = highest_productivity_move(board);
    }

    return best_move;
}

// Assumes there is at least one move to make
Quad AI::get_dumbass_move(Board board)
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

Quad AI::highest_productivity_move(Board board)
{
    QList<Quad> empty_quads = board.quads_with_piece("");

    Quad highest_p_quad = empty_quads[0];
    int highest_productivity = board.productivity(QUAD_TOP_LEFT, piece_type);
    foreach (Quad quad, empty_quads)
    {
        int p = board.productivity(quad, piece_type);

        if (p > highest_productivity)
        {
            highest_productivity = p;
            highest_p_quad = quad;
        }
    }

    return highest_p_quad;
}

void AI::set_piece_type(QString piece)
{
    piece_type = piece;
}

QString AI::get_piece()
{
    return piece_type;
}
