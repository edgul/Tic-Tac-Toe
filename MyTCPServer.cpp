#include "MyTCPServer.h"

#include <iostream>
#include "config.h"

MyTCPServer::MyTCPServer()
{
    socket = 0;

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
    if (socket)
    {
        std::cout << "Cannot form new connection. Socket busy";

        return;
    }

    socket = nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), SLOT(receive_data()));
    connect(socket, SIGNAL(aboutToClose()), SLOT(close_connection()));

    std::cout << "Connection formed\n";

}

void MyTCPServer::receive_data()
{

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
    // print remaining data
    QByteArray data = socket->readAll();
    std::cout << data.data();

    std::cout << "Connection closed\n";
    socket = 0;
}

void MyTCPServer::flush_output()
{
    std::flush(std::cout);
}
