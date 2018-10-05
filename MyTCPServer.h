#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "data.h"


class MyTCPServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTCPServer();

private slots:
    void new_connection();
    void receive_data();
    void close_connection();

    void flush_output();

    void send_loop();

private:

    void send_hello_world(QTcpSocket * socket, QString string);
    void send_handshake_response(QTcpSocket * socket, Handshake h);
    void send_delimited_message(QTcpSocket *socket, QByteArray bytes);

    QList<QTcpSocket *> sockets;
    QList<QString> socket_buffers;

    QTimer flush_timer;

    void unpack_data(QByteArray data );

    QString left_overs;

    QTimer send_timer;
};

#endif // MYTCPSERVER_H
