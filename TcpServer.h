#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "data/data.h"
#include "data/Message.h"


class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer();

    void sendMessage(Message msg, int user);

signals:
    void receivedData(QString data, int user);
    void userDisconnected(int user);

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

    QTcpServer tcpServer_;
};

#endif // MYTCPSERVER_H
