#include "MyTCPClient.h"

#include <iostream>
#include "config.h"

MyTCPClient::MyTCPClient()
{
    state = UNCONNECTED;
    connect(&socket, SIGNAL(connected()), SLOT(connected()));
    connect(&socket, SIGNAL(readyRead()), SLOT(received_data()));
    connect(&socket, SIGNAL(aboutToClose()), SLOT(closing()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(flush_output()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

void MyTCPClient::connect_to_server()
{
    if (state == UNCONNECTED)
    {
        socket.connectToHost(HOST_ADDRESS, HOST_PORT);

        state = CONNECTING;
    }
}

void MyTCPClient::send(QString str)
{
    if (state != CONNECTED)
    {
        std::cout << "Failed to send. Not connected\n";
        return;
    }

    QByteArray data = str.toLatin1();

    socket.write(data);
}

void MyTCPClient::close()
{

    if (state == UNCONNECTED)
    {
        std::cout << "Cannot close connection. No connection.\n";
        return;
    }

    send(QString("Close"));

    socket.close();

}

void MyTCPClient::connected()
{
    
    state = CONNECTED;

    std::cout << "Connected to server.\n";
}

void MyTCPClient::received_data()
{
    QByteArray bytes = socket.readAll();

    std::cout << bytes.data();
}

void MyTCPClient::closing()
{
    state = UNCONNECTED;

    std::cout << "Closing connection.\n";
}

void MyTCPClient::flush_output()
{
    std::flush(std::cout);
}
