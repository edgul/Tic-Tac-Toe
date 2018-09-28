#include "Protocol.h"

#define DELIMITER "TTT"
#define PID_LENGTH 4

#define PID_STATE "STAT"
#define PID_MOVE  "MOVE"

#define PID_STATE_LENGTH (1)
#define PID_STATE_BOARD_LENGTH (9)

Protocol::Protocol()
{
    left_overs = "";
    connect(&tcp_client, SIGNAL(report(QString)), this, SLOT(received_data(QString)));

}

void Protocol::player_move(bool player_x, Quad q)
{
     QString data = DELIMITER + QString(PID_MOVE) + QString(player_x) + QString(q);
     tcp_client.send(data);

     QString report_data = "Sending " + data;
     emit report(report_data);
}

void Protocol::connect_to_server()
{
    tcp_client.connect_to_server();
}

void Protocol::close_connection()
{
    tcp_client.close();
}

void Protocol::received_data(QString data)
{
    QString all_data = left_overs + data;

    int i = 0;
    while (all_data.indexOf(DELIMITER, i) != -1)
    {
        int i = all_data.indexOf(DELIMITER) + 3;

        QString pid = all_data.mid(i, PID_LENGTH);
        i += PID_LENGTH;

        if (pid == PID_STATE)
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
    }

    left_overs = all_data.mid(i);
}
