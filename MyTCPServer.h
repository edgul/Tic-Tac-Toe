#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

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

private:

    QList<QTcpSocket *> sockets;
    QList<QString> socket_buffers;

    QTimer flush_timer;
};

#endif // MYTCPSERVER_H
