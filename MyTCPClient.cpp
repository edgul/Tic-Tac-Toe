#include "MyTCPClient.h"

#include <iostream>
#include "config.h"

MyTCPClient::MyTCPClient()
{
    state = DISCONNECTED;
    connect(&socket, SIGNAL(connected()), SLOT(connected()));
    connect(&socket, SIGNAL(readyRead()), SLOT(received_data()));
    connect(&socket, SIGNAL(aboutToClose()), SLOT(closing()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(flush_output()));
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

void MyTCPClient::send(QString str)
{
    if (state != CONNECTED)
    {
        emit report("ERR: Cannot send; Not connected\n");
        return;
    }

    QByteArray data = str.toLatin1();

    socket.write(data);
}

void MyTCPClient::close()
{

    if (state == DISCONNECTED)
    {
        emit report("ERR: No connection to close.\n");
        return;
    }

    send(QString("Close"));

    socket.close();

}

void MyTCPClient::connected()
{
    QByteArray bytes = socket.readAll();

    QString msg;

    state = CONNECTED;
    msg = "Connected to server.\n";

    emit report(msg);
}

void MyTCPClient::received_data()
{
    if (state == CONNECTED)
    {
        QByteArray bytes = socket.readAll();

        if (bytes.contains(SERVER_BUSY))
        {
            emit report("ERR: Server Busy.");
            socket.close();
        }
        else
        {
            emit report(QString(bytes));
        }
    }
}

void MyTCPClient::closing()
{
    if (state != DISCONNECTED)
    {
        state = DISCONNECTED;

        emit report("Connection Closed.\n");
    }
}

void MyTCPClient::flush_output()
{
    std::flush(std::cout);
}
