#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "data.h"
#include "Board.h"


enum TcpState
{
    DISCONNECTED,
    CONNECTING,
    CONNECTED
};

class MyTCPClient : public QObject
{
    Q_OBJECT
public:
    MyTCPClient();

    QTcpSocket socket;

    void connect_to_server();
    void send_message(QString str);
    void send(QString str);
    void close();

    void player_move(bool player_x, Quad q);

signals:
    void report(QString);
    void update_game_state(bool players_turn_x, Board board);

private slots:
    void connected();
    void received_data();
    void closing();

    void flush_output();
private:

    TcpState state;

    QTimer flush_timer;

    QByteArray left_overs;

};

#endif // MYTCPCLIENT_H
