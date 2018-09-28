#include "Player.h"

#include "Protocol.h"

Player::Player()
{
    connect(&protocol, SIGNAL(report(QString)), this, SLOT(received_report(QString)));
    connect(&protocol, SIGNAL(update_game_state(bool,Board)), this, SLOT(received_game_state(bool,Board)));
}

void Player::set_piece(bool x)
{
    piece_x = x;
}

void Player::connect_to_server()
{
    protocol.connect_to_server();
}

void Player::close_connection()
{
    protocol.close_connection();
}

void Player::init_board(BoardWidget * board_w)
{
    board_widget = board_w;
    connect(board_widget, SIGNAL(board_clicked(Quad)), this, SLOT(board_clicked(Quad)));

    board_widget->set_board(&board);
}

void Player::board_clicked(Quad quad)
{

    if (turn_x == piece_x) // this player's turn
    {
        protocol.player_move(turn_x, quad);
    }
}

void Player::received_report(QString r)
{
    emit report(r);
}

void Player::received_game_state(bool player_turn_x, Board new_board)
{
    turn_x = player_turn_x;

    board = new_board;
    board_widget->set_board(&board);
}
