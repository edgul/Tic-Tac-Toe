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

signals:
    void received_data(QString data);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onAboutToClose();

    void onFlushTimerTick();
    void onSendTimerTick();

private:
    void send_hello_world(QTcpSocket * socket, QString string);
    void send_handshake_response(QTcpSocket * socket, Handshake h);
    void send_delimited_message(QTcpSocket *socket, QByteArray bytes);

    void unpack_data(QByteArray data );

    QString left_overs;

    QList<QTcpSocket *> sockets;
    QList<QString> socket_buffers;

    QTimer flush_timer;
    QTimer send_timer;
};

#endif // MYTCPSERVER_H
