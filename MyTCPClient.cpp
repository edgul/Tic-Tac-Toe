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

void MyTCPClient::connect_to_server()
{
    if (state == DISCONNECTED)
    {
        socket.connectToHost(HOST_ADDRESS, HOST_PORT);
        state = CONNECTING;
    }
}

void MyTCPClient::send_message(QString str)
{
    QString string_to_send = str + QString(DELIMITER);

    if (state != CONNECTED)
    {
        emit report("Client ERR: Cannot send; Not connected\n");
        return;
    }

    emit report("Client Sending: " + string_to_send);

    QByteArray data = string_to_send.toLatin1();
    socket.write(data);
}

void MyTCPClient::disconnect_from_server()
{
    if (state == DISCONNECTED)
    {
        emit report("Client ERR: No connection to close.\n");
        return;
    }

    send_message("Close");
}

void MyTCPClient::onSocketConnected()
{
    state = CONNECTED;
    onReadyRead();
}

void MyTCPClient::onSocketDisconnected()
{
    qDebug() << "Client socket disconnected";
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


