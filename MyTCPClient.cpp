#include "MyTCPClient.h"

#include <iostream>
#include "config.h"

MyTCPClient::MyTCPClient()
{
    state = DISCONNECTED;
    connect(&socket, SIGNAL(connected()), SLOT(onSocketConnected()));
    connect(&socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(&socket, SIGNAL(disconnected()), SLOT(onSocketDisconnected()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(onFlushTimerTick()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

void MyTCPClient::connectToServer()
{
    if (state == DISCONNECTED)
    {
        socket.connectToHost(HOST_ADDRESS, HOST_PORT);
        state = CONNECTING;
    }
}

void MyTCPClient::sendMessage(Message msg)
{
    QString msgToSend = msg.toString() + QString(DELIMITER);

    if (state != CONNECTED)
    {
        emit report("Client ERR: Cannot send; Not connected\n");
        return;
    }

    // qDebug() << "Client sending message: " << msgToSend;
    // emit report("Client Sending Message: " + msgToSend);

    QByteArray data = msgToSend.toLatin1();
    socket.write(data);
}

void MyTCPClient::disconnectFromServer()
{
    if (state == DISCONNECTED)
    {
        emit report("Client ERR: No connection to close.\n");
        return;
    }

    qDebug() << "Client disconnecting";
    socket.disconnectFromHost();
}

void MyTCPClient::onSocketConnected()
{
    state = CONNECTED;
    onReadyRead();
}

void MyTCPClient::onSocketDisconnected()
{
    state = DISCONNECTED;
    emit report("Connection Closed.\n");
}

void MyTCPClient::onReadyRead()
{
    if (state == CONNECTED)
    {
        emit receivedData(socket.readAll());
    }
}

void MyTCPClient::onFlushTimerTick()
{
    std::flush(std::cout);
}


