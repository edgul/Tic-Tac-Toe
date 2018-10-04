#ifndef PLAYER_H
#define PLAYER_H

#include "BoardWidget.h"
#include "MyTCPClient.h"

class Player : public QObject
{
    Q_OBJECT
public:
    Player();

    void set_piece(bool x);

    void connect_to_server();
    void close_connection();

    void init_board(BoardWidget * board_w);

signals:
    void report(QString);

private slots:
    void board_clicked(Quad quad);
    void received_report(QString r );
    void received_game_state(bool player_turn_x, Board new_board);

private:

    Board board;

    MyTCPClient tcp_client;

    bool piece_x;
    bool turn_x;

    BoardWidget * board_widget;

};

#endif // PLAYER_H
