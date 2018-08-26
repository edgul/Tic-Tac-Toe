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
}

void Game::set_board(BoardWidget * board_widget)
{
    this->board_widget = board_widget;
    connect(this->board_widget, SIGNAL(board_clicked(Quad)), this, SLOT(board_clicked(Quad)));
}

void Game::start()
{
    board_widget->clear();
    turn_x = true;

    QString msg = MSG_TURN_X;
    emit update_msg_label(msg);

    active = true;

}

void Game::board_clicked(Quad quad)
{
    if (active)
    {
        // place move
        if (board_widget->quad_empty(quad)) // valid move
        {
            if (turn_x)
            {
                board_widget->place_x(quad);
            }
            else
            {
                board_widget->place_o(quad);
            }

            turn_x = !turn_x;

            QString msg = MSG_TURN_X;
            if (!turn_x) msg = MSG_TURN_O;
            emit update_msg_label(msg);

            // check for end-game
            if (board_widget->winner() == PLAYER_X) // x wins
            {
                QString msg = MSG_WIN_X;
                emit update_msg_label(msg);

                active = false;
            }
            else if (board_widget->winner() == PLAYER_O) // o wins
            {
                QString msg = MSG_WIN_O;
                emit update_msg_label(msg);

                active = false;
            }
            else if (board_widget->full()) // tie
            {
                QString msg = MSG_TIE;
                emit update_msg_label(msg);

                active = false;
            }
        }
    }
}

