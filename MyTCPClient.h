#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "data/data.h"
#include "data/BoardModel.h"
#include "data/Message.h"

class MyTCPClient : public QObject
{
    Q_OBJECT
public:
    MyTCPClient();

    bool isConnected();
    void connectToServer();
    void disconnectFromServer();
    void sendMessage(Message msg);

signals:
    void report(QString);
    void receivedData(QByteArray data);

private slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onReadyRead();
    void onFlushTimerTick();

private:
    QTcpSocket socket;
    QTimer flush_timer;

};

#endif // MYTCPCLIENT_H
