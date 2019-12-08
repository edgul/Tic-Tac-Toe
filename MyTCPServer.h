#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "data.h"
#include "Message.h"


class MyTCPServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTCPServer();

    void sendMessage(Message msg, int user);

signals:
    void receivedData(QString data, int user);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onAboutToClose();
    void onFlushTimerTick();
    void onDisconnected();

private:
    int userCount;
    QList<QTcpSocket *> sockets;
    QList<QString> socket_buffers;
    QMap<int, QTcpSocket*> users;

    QTimer flush_timer;

};

#endif // MYTCPSERVER_H
