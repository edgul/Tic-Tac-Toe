#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>
#include "data.h"
#include "MyTCPClient.h"
#include "Board.h"

class Protocol : public QObject
{
    Q_OBJECT
public:
    Protocol();

    void player_move(bool player_x, Quad q);

    void connect_to_server();
    void close_connection();

signals:
    void report(QString r);
    void update_game_state(bool player_turn_x, Board board);

private slots:
    void received_data(QString data);

private:
    MyTCPClient tcp_client;

    QString left_overs;



};

#endif // PROTOCOL_H
