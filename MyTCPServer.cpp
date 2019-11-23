#include "MyTCPServer.h"

#include <iostream>
#include "config.h"
#include "Board.h"

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

    connect(this, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    connect(&flush_timer, SIGNAL(timeout()),SLOT(onFlushTimerTick()));
    flush_timer.setInterval(1000);
    flush_timer.start();

    connect(&send_timer, SIGNAL(timeout()),SLOT(onSendTimerTick()));
    send_timer.setInterval(2000);
}

void MyTCPServer::onNewConnection()
{
    if (sockets.length() >= MAX_SOCKETS)
    {
        std::cout << "Cannot form new connection. Server busy";

        QTcpSocket * new_socket = nextPendingConnection();
        send_handshake_response(new_socket, HANDSHAKE_BUSY);
        new_socket->close();

        return;
    }

    QTcpSocket * new_socket = nextPendingConnection();
    connect(new_socket, SIGNAL(readyRead()), SLOT(onReadyRead()));
    connect(new_socket, SIGNAL(aboutToClose()), SLOT(onAboutToClose()));

    send_handshake_response(new_socket, HANDSHAKE_OK);

    sockets.append(new_socket);

    std::cout << "Connection formed\n";

    // start the send loop
    send_timer.start();

}

void MyTCPServer::onReadyRead()
{
    QTcpSocket * socket = (QTcpSocket *) sender();
    QByteArray data = socket->readAll();

    unpack_data(data);

    QByteArray terminate_string = "Close";
    if (data.contains(terminate_string))
    {
        socket->close();
    }
    else
    {
        emit received_data(data);
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

void MyTCPServer::onSendTimerTick()
{
    for (int i = 0; i < sockets.length(); i++)
    {
        QTcpSocket * socket = sockets[i];

        QString i_str = QString::number(i);
        send_hello_world(socket, "hello world " + i_str);

        QString msg = "SERVER: Wrote to socket " + QString::number(i) + "\n";
        std::cout << msg.toLatin1().data();

    }
}

void MyTCPServer::send_hello_world(QTcpSocket *socket, QString string)
{
    QByteArray msg = QString::number(FUNCTION_HELLO_WORLD).toLatin1() + SEPARATOR +
                     string.toLatin1();

    send_delimited_message(socket, msg);
}

void MyTCPServer::send_handshake_response(QTcpSocket * socket, Handshake h)
{

    QByteArray handshake = QString::number(FUNCTION_HANDSHAKE_RESPONSE).toLatin1() + SEPARATOR +
                           QString::number(h).toLatin1();

    send_delimited_message(socket, handshake);

}

void MyTCPServer::send_delimited_message(QTcpSocket * socket, QByteArray bytes)
{
    if (socket == 0) return;

    socket->write("TTT " + bytes + " ");
}

void MyTCPServer::unpack_data(QByteArray data)
{
//    QString all_data = left_overs + QString(data);

//    int i = 0;
//    while (all_data.indexOf(DELIMITER, i) != -1)
//    {
//        int i = all_data.indexOf(DELIMITER) + 3;

//        QString pid = all_data.mid(i, PID_LENGTH);
//        i += PID_LENGTH;

//        if (pid == PID_MOVE)
//        {
//            QString turn_x = all_data.mid(i, PID_STATE_LENGTH);
//            bool player_turn_x = true;
//            if (turn_x == "F") player_turn_x = false;

//            i += PID_STATE_LENGTH;

//            QString board_string = all_data.mid(i, PID_STATE_BOARD_LENGTH);
//            i += PID_STATE_BOARD_LENGTH;

//            Board board;
//            board.set_board_from_string(board_string);

//            emit update_game_state(player_turn_x, board);
//        }
//    }
}

