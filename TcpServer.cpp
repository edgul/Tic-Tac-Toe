#include "TcpServer.h"

#include <iostream>
#include "data/config.h"
#include "data/BoardModel.h"

#define MAX_SOCKETS (4)


TcpServer::TcpServer() :
    userCount(0)
{

    QHostAddress host_address(HOST_ADDRESS);
    if (!tcpServer_.listen(host_address, HOST_PORT))
    {
        std::cout << "Failed to listen";
        return;
    }

    std::cout << "Listening on " << HOST_ADDRESS << ":" << HOST_PORT << std::endl;

    connect(&tcpServer_, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(onFlushTimerTick()));
    flush_timer.setInterval(1000);
    flush_timer.start();
}

void TcpServer::sendMessage(Message msg, int user)
{
    if (users.contains(user))
    {
        qDebug() << "Server sending message to User: " << user;
        QTcpSocket *socket = users[user];
        QString toSend = msg.toString() + QString(DELIMITER);
        QByteArray data = toSend.toLatin1();
        socket->write(data);
    }
}

void TcpServer::onNewConnection()
{
    if (sockets.length() >= MAX_SOCKETS)
    {
        std::cout << "Cannot form new connection. Server busy";

        QTcpSocket * new_socket = tcpServer_.nextPendingConnection();
        new_socket->close();
        return;
    }

    QTcpSocket * new_socket = tcpServer_.nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(new_socket, SIGNAL(aboutToClose()), SLOT(onAboutToClose()));
    connect(new_socket, SIGNAL(disconnected()), SLOT(onDisconnected()));

    sockets.append(new_socket);
    users.insert(userCount, new_socket);

    qDebug() << "SERVER: connection formed with user:  "<< userCount;
    userCount++;
}

void TcpServer::onReadyRead()
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

void TcpServer::onAboutToClose()
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

void TcpServer::onFlushTimerTick()
{
    std::flush(std::cout);
}

void TcpServer::onDisconnected()
{
    qDebug() << "SERVER: client disconnected";

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
        qDebug() << "SERVER: removed user from user list: " << removeUser;
        users.remove(removeUser);
        sockets.removeOne(socket);
        emit userDisconnected(removeUser);
    }
}
