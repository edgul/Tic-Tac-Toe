#include "MyTCPClient.h"

#include <iostream>
#include "config.h"

MyTCPClient::MyTCPClient()
{

    left_overs = "";

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

void MyTCPClient::send_message(QString str)
{
    QString string_to_send = QString(DELIMITER) + str;
    send(string_to_send);
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

    send_message("Close");

    socket.close();

}

void MyTCPClient::connected()
{

    state = CONNECTED;

    received_data();

}

void MyTCPClient::received_data()
{
    if (state == CONNECTED)
    {
        QByteArray all_data = left_overs + socket.readAll();

        int i = 0;
        while (all_data.indexOf(DELIMITER, i) != -1)
        {
            i = all_data.indexOf(DELIMITER) + DELIMITER_LENGTH;

            Function function = (Function) all_data.mid(i, FUNCTION_LENGTH).toInt();
            i += FUNCTION_LENGTH + 1;

            if (function == FUNCTION_HANDSHAKE_RESPONSE)
            {
                int next_separator = all_data.indexOf(SEPARATOR, i);
                QByteArray handshake_response = all_data.mid(i, next_separator - i);
                Handshake response = (Handshake) handshake_response.toInt();

                i = next_separator + 1;

                if (response == HANDSHAKE_OK)
                {
                    emit report("Connected to Server.");
                }
                else
                {
                    emit report("ERR: Server Busy.");
                    socket.close();
                }
            }
            else if (function == FUNCTION_UPDATE_BOARD)
            {
                QString turn_x = all_data.mid(i, PID_STATE_LENGTH);
                bool player_turn_x = true;
                if (turn_x == "F") player_turn_x = false;

                i += PID_STATE_LENGTH;

                QString board_string = all_data.mid(i, PID_STATE_BOARD_LENGTH);
                i += PID_STATE_BOARD_LENGTH;

                Board board;
                board.set_board_from_string(board_string);

                emit update_game_state(player_turn_x, board);
            }
            else if (function == FUNCTION_HELLO_WORLD) // o cutoff
            {
                int next_separator = all_data.indexOf(SEPARATOR, i);
                QByteArray msg = all_data.mid(i, next_separator - i);
                i = next_separator + 1;

                next_separator = all_data.indexOf(SEPARATOR, i);
                QByteArray msg2 = all_data.mid(i, next_separator - i);
                i = next_separator + 1;

                next_separator = all_data.indexOf(SEPARATOR, i);
                QByteArray msg3 = all_data.mid(i, next_separator - i);
                i = next_separator + 1;

                emit report(msg + msg2 + msg3);
            }

        }

        left_overs = all_data.mid(i);
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

void MyTCPClient::player_move(bool player_x, Quad q)
{
     QString data = DELIMITER + QString(PID_MOVE) + QString(player_x) + QString(q);
     send(data);

     QString report_data = "Sending " + data;
     emit report(report_data);
}
