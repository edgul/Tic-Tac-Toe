#include "MyTCPServer.h"

#include <iostream>
#include "config.h"
#include "BoardModel.h"

#define MAX_SOCKETS (4)


MyTCPServer::MyTCPServer() :
    userCount(0)
{

    QHostAddress host_address(HOST_ADDRESS);
    if (!listen(host_address, HOST_PORT))
    {
        std::cout << "Failed to listen";

        return;
    }

    std::cout << "Listening on " << HOST_ADDRESS << ":" << HOST_PORT << std::endl;

    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(onFlushTimerTick()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

void MyTCPServer::sendMessage(Message msg, int user)
{
    if (users.contains(user))
    {
        QTcpSocket *socket = users[user];
        QString toSend = msg.toString() + QString(DELIMITER);
        QByteArray data = toSend.toLatin1();
        socket->write(data);
    }
}

void MyTCPServer::onNewConnection()
{
    if (sockets.length() >= MAX_SOCKETS)
    {
        std::cout << "Cannot form new connection. Server busy";

        QTcpSocket * new_socket = nextPendingConnection();
        new_socket->close();
        return;
    }

    QTcpSocket * new_socket = nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(new_socket, SIGNAL(aboutToClose()), SLOT(onAboutToClose()));
    connect(new_socket, SIGNAL(disconnected()), SLOT(onDisconnected()));

    sockets.append(new_socket);
    users.insert(userCount, new_socket);

    std::cout << "Connection formed with user: " << userCount<< "\n";
    userCount++;
}

void MyTCPServer::onReadyRead()
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
        int foundUser = -1;
        foreach (int user, users.keys())
        {
            if (socket == users[user])
            {
                foundUser = user;
                break;
            }
        }

        if (foundUser != -1)
        {
            emit receivedData(data, foundUser);
        }
        else
        {
            qDebug() << "SERVER: failed to find user for socket";
            Q_ASSERT(false);
        }
    }
}

void MyTCPServer::onAboutToClose()
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

void MyTCPServer::onFlushTimerTick()
{
    std::flush(std::cout);
}

void MyTCPServer::onDisconnected()
{
    QTcpSocket * socket = (QTcpSocket *) sender();

    int removeUser = -1;
    foreach (int user, users.keys())
    {
        if (socket == users[user])
        {
            removeUser = user;
            break;
        }
    }

    if (removeUser != -1)
    {
        users.remove(removeUser);
        emit userDisconnected(removeUser);
    }
}
