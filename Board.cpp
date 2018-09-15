#include "Board.h"

Board::Board()
{
    define_winning_sets();

    // init empty board
    for (int i = 0; i < 9; i++)
    {
        board.append("");
    }
}

void Board::clear()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = "";
    }
}

bool Board::full()
{
    bool full = true;

    foreach (QString s, board)
    {
        if (s == "")
        {
            full = false;
            break;
        }
    }

    return full;
}

void Board::place(QString piece, Quad q)
{
    int q_int = (int) q;
    board[q_int] = piece;
}

bool Board::quad_empty(Quad quad)
{
    bool empty = false;

    if (board[quad] == "") empty = true;

    return empty;
}

QString Board::winner()
{
    QString winner = "";

    foreach (QList<Quad> win, wins)
    {
        bool these_quads_win = true;

        foreach(Quad quad, win)
        {
            if (!quads_with_piece(PLAYER_X).contains(quad))
            {
                these_quads_win = false;
            }
        }

        if (these_quads_win)
        {
            winner = PLAYER_X;
            break;
        }

        these_quads_win = true;

        foreach(Quad quad, win)
        {
            if (!quads_with_piece(PLAYER_O).contains(quad))
            {
                these_quads_win = false;
            }
        }

        if (these_quads_win)
        {
            winner = PLAYER_O;
            break;
        }
    }

    return winner;
}

int Board::size()
{
    return board.length();
}

QString Board::piece_at(int index)
{
    return board[index];
}

QList<Quad> Board::quads_with_piece(QString piece)
{
    QList<Quad> quads;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] == piece)
        {
            quads.append( (Quad) i);
        }
    }

    return quads;
}

void Board::define_winning_sets()
{
    QList<Quad> h_top = QList<Quad>() << QUAD_TOP_LEFT << QUAD_TOP_MID << QUAD_TOP_RIGHT;
    QList<Quad> h_mid = QList<Quad>() << QUAD_MID_LEFT << QUAD_MID_MID << QUAD_MID_RIGHT;
    QList<Quad> h_bot = QList<Quad>() << QUAD_BOT_LEFT << QUAD_BOT_MID << QUAD_BOT_RIGHT;

    QList<Quad> v_left = QList<Quad>() << QUAD_TOP_LEFT  << QUAD_MID_LEFT << QUAD_BOT_LEFT;
    QList<Quad> v_mid  = QList<Quad>() << QUAD_TOP_MID   << QUAD_MID_MID << QUAD_BOT_MID;
    QList<Quad> v_right =QList<Quad>() << QUAD_TOP_RIGHT << QUAD_MID_RIGHT << QUAD_BOT_RIGHT;

    QList<Quad> d_r    = QList<Quad>() << QUAD_BOT_LEFT << QUAD_MID_MID << QUAD_TOP_RIGHT;
    QList<Quad> d_l    = QList<Quad>() << QUAD_BOT_RIGHT << QUAD_MID_MID << QUAD_TOP_LEFT;

    wins.append(h_top);
    wins.append(h_mid);
    wins.append(h_bot);

    wins.append(v_left);
    wins.append(v_mid);
    wins.append(v_right);

    wins.append(d_r);
    wins.append(d_l);
}
