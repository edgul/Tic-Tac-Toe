#include "Board.h"


Board::Board()
{
    define_winning_sets();

    // init empty board
    for (int i = 0; i < 9; i++)
    {
        board.append(EMPTY_CELL);
    }
}

void Board::clear()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = EMPTY_CELL;
    }
}

bool Board::full()
{
    bool full = true;

    foreach (QString s, board)
    {
        if (s == EMPTY_CELL)
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

    if (board[quad] == EMPTY_CELL) empty = true;

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

int Board::pieces()
{
    int p = 0;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] != EMPTY_CELL)
        {
            p++;
        }
    }

    return p;
}

int Board::size()
{
    return board.length();
}

QString Board::piece_at(int index)
{
    return board[index];
}

int Board::productivity(Quad move, QString piece_type)
{
    int p = 0;

    QString other_piece = PLAYER_X;
    if (piece_type == PLAYER_X) other_piece = PLAYER_O;

    foreach (QList<Quad> win_line, wins)
    {
        if (win_line.contains(move))
        {
            bool has_other_piece = false;
            foreach (Quad i , win_line)
            {
                if (board[i] == other_piece)
                {
                    has_other_piece = true;
                    break;
                }
            }

            if (!has_other_piece)
            {

                p++;
            }
        }
    }

    return p;
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

Quad Board::available_win(QString piece_type)
{
    Quad win_quad = QUAD_NONE;

    QList<Quad> empty_quads = quads_with_piece(EMPTY_CELL);

    foreach (Quad quad, empty_quads)
    {
        foreach (QList<Quad> win_line, wins)
        {
            int count = 0;
            if (win_line.contains(quad))
            {
                foreach( Quad q, win_line)
                {
                    if (board[q] == piece_type)
                    {
                        count ++;
                    }
                }
            }

            if (count == 2)
            {
                win_quad = quad;
                break;
            }
        }
    }

    return win_quad;
}

QString Board::toString()
{
    return board.join("");
}

void Board::set_board_from_string(QString b_string)
{
    QList<QString> list = b_string.split("");

    board = list;
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
