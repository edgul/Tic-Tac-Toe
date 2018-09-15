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

}

void Game::set_board(BoardWidget * board_w)
{
    board_widget = board_w;
    connect(board_widget, SIGNAL(board_clicked(Quad)), this, SLOT(board_clicked(Quad)));

    board_widget->set_board(&board);
}

void Game::init()
{
    board.clear();
    board_widget->repaint();

    turn_x = true;

    QString msg = MSG_TURN_X;
    emit update_msg_label(msg);

    active = true;

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
    if (board.winner() == PLAYER_X) // x wins
    {
        QString msg = MSG_WIN_X;
        emit update_msg_label(msg);

        game_over = true;

    }
    else if (board.winner() == PLAYER_O) // o wins
    {
        QString msg = MSG_WIN_O;
        emit update_msg_label(msg);

        game_over = true;
    }
    else if (board.full()) // tie
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
        if (board.quad_empty(quad)) // valid move
        {
            // Place piece
            QString piece = get_turn_piece();
            board.place(piece, quad);

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
    board.place(piece, best_move);

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

