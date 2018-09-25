#include "MyTCPServer.h"

#include <iostream>
#include "config.h"

#define MAX_SOCKETS (4)

MyTCPServer::MyTCPServer()
{

    QHostAddress host_address(HOST_ADDRESS);
    if (!listen(host_address, HOST_PORT))
    {
        std::cout << "Failed to listen";

        return;
    }

    std::cout << "Listening on " << HOST_ADDRESS << ":" << HOST_PORT << std::endl;

    connect(this, SIGNAL(newConnection()), this, SLOT(new_connection()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(flush_output()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

void MyTCPServer::new_connection()
{
    if (sockets.length() >= MAX_SOCKETS)
    {
        std::cout << "Cannot form new connection. Server busy";

        QTcpSocket * new_socket = nextPendingConnection();
        new_socket->write(SERVER_BUSY);
        new_socket->close();

        return;
    }

    QTcpSocket * new_socket = nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), SLOT(receive_data()));
    connect(new_socket, SIGNAL(aboutToClose()), SLOT(close_connection()));

    new_socket->write(SERVER_OK);

    sockets.append(new_socket);

    std::cout << "Connection formed\n";

}

void MyTCPServer::receive_data()
{
    QTcpSocket * socket = (QTcpSocket *) sender();
    QByteArray data = socket->readAll();

    QByteArray terminate_string = "Close";
    if (data.contains(terminate_string))
    {
        socket->close();
    }
    else
    {
        std::cout << data.data();
    }
}

void MyTCPServer::close_connection()
{
    QTcpSocket * sending_socket = (QTcpSocket *) sender();

    // print remaining data
    QByteArray data = sending_socket->readAll();
    std::cout << data.data();

    for (int i = 0; i < sockets.length(); i++)
    {
        QTcpSocket * socket = sockets[i];

        if (socket == sending_socket)
        {
            socket_buffers.removeAt(i);
            sockets.removeAt(i);

            sending_socket->deleteLater();

            std::cout << "Connection closed\n";
        }
    }
}

void MyTCPServer::flush_output()
{
    std::flush(std::cout);
}
