#include "MyTCPClient.h"

#include <iostream>
#include "config.h"

MyTCPClient::MyTCPClient()
{
    connect(&socket, SIGNAL(connected()), SLOT(onSocketConnected()));
    connect(&socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(&socket, SIGNAL(disconnected()), SLOT(onSocketDisconnected()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(onFlushTimerTick()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

bool MyTCPClient::isConnected()
{
    return socket.state() == QAbstractSocket::ConnectedState;
}

void MyTCPClient::connectToServer()
{
    if (socket.state() == QAbstractSocket::UnconnectedState)
    {
        socket.connectToHost(HOST_ADDRESS, HOST_PORT);
    }
}

void MyTCPClient::sendMessage(Message msg)
{
    QString msgToSend = msg.toString() + QString(DELIMITER);

    if (socket.state() != QAbstractSocket::ConnectedState)
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
    qDebug() << "state: " << socket.state();
    if (socket.state() != QAbstractSocket::ConnectedState)
    {
        emit report("Client ERR: No connection to close.\n");
        return;
    }

    qDebug() << "Client disconnecting";
    socket.disconnectFromHost();
}

void MyTCPClient::onSocketConnected()
{
    onReadyRead();
}

void MyTCPClient::onSocketDisconnected()
{
    emit report("Connection Closed.\n");
}

void MyTCPClient::onReadyRead()
{
    emit receivedData(socket.readAll());
}

void MyTCPClient::onFlushTimerTick()
{
    std::flush(std::cout);
}


