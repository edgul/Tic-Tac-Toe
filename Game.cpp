#include "Game.h"

#define MSG_TURN_X "X's turn"
#define MSG_TURN_O "O's turn"
#define MSG_WIN_X  "X wins!"
#define MSG_WIN_O  "O wins!"
#define MSG_TIE    "Tie game."


Game::Game()
{
    turn_x = true;
    active = false;

    one_player = true;

    // empty board
    for (int i = 0; i < 9; i++)
    {
        board.append("");
    }

    define_winning_sets();
}

void Game::set_board(BoardWidget * board_w)
{
    board_widget = board_w;
    connect(board_widget, SIGNAL(board_clicked(Quad)), this, SLOT(board_clicked(Quad)));

    board_widget->set_board(&board);
}

void Game::init()
{
    clear();
    turn_x = true;

    QString msg = MSG_TURN_X;
    emit update_msg_label(msg);

    active = true;
}

void Game::clear()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = "";
    }

    board_widget->repaint();
}

bool Game::full()
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

void Game::start_multiplayer()
{
    init();

    one_player = false;

}

void Game::start_one_player()
{
    init();

    one_player = true;

}

void Game::turn_cleanup()
{
    bool game_over = false;

    // check for game over
    if (winner() == PLAYER_X) // x wins
    {
        QString msg = MSG_WIN_X;
        emit update_msg_label(msg);

        game_over = true;

    }
    else if (winner() == PLAYER_O) // o wins
    {
        QString msg = MSG_WIN_O;
        emit update_msg_label(msg);

        game_over = true;
    }
    else if (full()) // tie
    {
        QString msg = MSG_TIE;
        emit update_msg_label(msg);

        game_over = true;
    }

    if (game_over)
    {
        // stop taking user input when the game is over
        active = false;
    }
    else
    {
        turn_x = !turn_x;

        // update label
        QString msg = MSG_TURN_X;
        if (!turn_x) msg = MSG_TURN_O;
        emit update_msg_label(msg);

        // disable user input for one player game
        active = true;
        if (one_player)
        {
            if (!turn_x)
            {
                active = false;
            }
        }
    }
}

void Game::board_clicked(Quad quad)
{
    if (active) // accepting input from user
    {
        if (quad_empty(quad)) // valid move
        {
            // Place piece
            QString piece = get_turn_piece();
            place(piece, quad);

            turn_cleanup();

            if (one_player && !turn_x)
            {
                ai_goes();
            }
        }
    }
}

void Game::ai_goes()
{
    // ai actually goes
    Quad best_move = ai.get_move(board);
    QString piece = get_turn_piece();
    place(piece, best_move);

    turn_cleanup();
}

QString Game::get_turn_piece()
{
    QString turn_piece;
    if (turn_x)
    {
        turn_piece = PLAYER_X;
    }
    else
    {
        turn_piece = PLAYER_O;
    }

    return turn_piece;
}

void Game::place(QString xo, Quad q)
{
    int q_int = (int) q;
    board[q_int] = xo;
}

bool Game::quad_empty(Quad quad)
{
    bool empty = false;
    if (board[quad] == "") empty = true;

    return empty;
}

QString Game::winner()
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

QList<Quad> Game::quads_with_piece(QString piece)
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

void Game::define_winning_sets()
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

