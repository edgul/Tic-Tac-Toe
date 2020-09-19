#include "TcpClient.h"

#include <iostream>
#include "data/config.h"

TcpClient::TcpClient()
{
    connect(&socket, SIGNAL(connected()), SLOT(onSocketConnected()));
    connect(&socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(&socket, SIGNAL(disconnected()), SLOT(onSocketDisconnected()));
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onSocketError(QAbstractSocket::SocketError)));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(onFlushTimerTick()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

bool TcpClient::isConnected()
{
    return socket.state() == QAbstractSocket::ConnectedState;
}

void TcpClient::connectToServer()
{
    if (socket.state() == QAbstractSocket::UnconnectedState)
    {
        socket.connectToHost(HOST_ADDRESS, HOST_PORT);
    }
}

void TcpClient::sendMessage(Message msg)
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

void TcpClient::disconnectFromServer()
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

void TcpClient::onSocketConnected()
{
    emit connected();
    onReadyRead();
}

void TcpClient::onSocketDisconnected()
{
    emit report("Connection Closed.\n");
    emit disconnected();
}

void TcpClient::onReadyRead()
{
    emit receivedData(socket.readAll());
}

void TcpClient::onSocketError(QAbstractSocket::SocketError err)
{
    emit error(err);
}

void TcpClient::onFlushTimerTick()
{
    std::flush(std::cout);
}


