#include "ClientWindow.h"
#include "ui_ClientWindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    board_widget = ui->board_widget;

    connect(board_widget, SIGNAL(board_clicked(Quad)), SLOT(onBoardClicked(Quad)));
    connect(&game, SIGNAL(update_msg_label(QString)), SLOT(onGameUpdateMsgLabel(QString)));
    connect(&tcp_client, SIGNAL(report(QString)), SLOT(onTcpClientReport(QString)));
    connect(&tcp_client, SIGNAL(receivedData(QByteArray)), SLOT(onTcpClientReceivedData(QByteArray)));
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::set_player(bool x)
{
    piece_x = x;
}

void ClientWindow::on_button_start_clicked()
{

    if (ui->radio_multi_player->isChecked())
    {
        // game.start_multiplayer();
    }
    else
    {
        Difficulty difficulty = DIFFICULTY_EASY;
        if (ui->radio_difficulty_medium->isChecked()) difficulty = DIFFICULTY_MEDIUM;
        if (ui->radio_difficulty_hard->isChecked()) difficulty = DIFFICULTY_HARD;

        game.start_one_player(difficulty);
    }
}

void ClientWindow::onGameUpdateMsgLabel(QString msg)
{
    ui->label_msg->setText(msg);
}

void ClientWindow::onTcpClientReport(QString msg)
{
    ui->output->appendPlainText(msg);
}

void ClientWindow::on_button_connect_clicked()
{
    tcp_client.connect_to_server();
}

void ClientWindow::on_button_close_connection_clicked()
{
    tcp_client.disconnect_from_server();
}

void ClientWindow::on_radio_one_player_clicked()
{
    ui->frame_difficulty->setEnabled(true);
}

void ClientWindow::on_radio_multi_player_clicked()
{
    ui->frame_difficulty->setEnabled(false);
}

void ClientWindow::onBoardClicked(Quad quad)
{
    if (turn_x == piece_x)
    {
        QString data = QString(PID_MOVE) + QString(turn_x) + QString(quad);
        tcp_client.send_message(data);
    }
}

void ClientWindow::onTcpClientReceivedData(QByteArray data)
{
    QByteArray all_data = left_overs + data;

    int i = 0;
    while (all_data.indexOf(DELIMITER, i) != -1)
    {
        i = all_data.indexOf(DELIMITER) + DELIMITER_LENGTH;

        Function function = (Function) all_data.mid(i, FUNCTION_LENGTH).toInt();
        i += FUNCTION_LENGTH + 1;

        if (function == FUNCTION_HANDSHAKE_RESPONSE)
        {
            qDebug() << "TcpClient::Handshake Response";

            int next_separator = all_data.indexOf(SEPARATOR, i);
            QByteArray handshake_response = all_data.mid(i, next_separator - i);
            Handshake response = (Handshake) handshake_response.toInt();

            i = next_separator + 1;

            if (response == HANDSHAKE_OK)
            {
                report("Connected to Server.");
            }
            else
            {
                report("ERR: Server Busy.");
            }
        }
        else if (function == FUNCTION_UPDATE_BOARD)
        {
            qDebug() << "TCPClient::updating board";
            QString turn_x = all_data.mid(i, PID_STATE_LENGTH);
            bool player_turn_x = true;
            if (turn_x == "F") player_turn_x = false;

            i += PID_STATE_LENGTH;

            QString board_string = all_data.mid(i, PID_STATE_BOARD_LENGTH);
            i += PID_STATE_BOARD_LENGTH;

            Board board;
            board.set_board_from_string(board_string);

            update_game_state(player_turn_x, board);
        }
        else if (function == FUNCTION_HELLO_WORLD) // o cutoff
        {
            qDebug() << "TCPClient::Hello World";

            int next_separator = all_data.indexOf(SEPARATOR, i);
            QByteArray msg = all_data.mid(i, next_separator - i);
            i = next_separator + 1;

            next_separator = all_data.indexOf(SEPARATOR, i);
            QByteArray msg2 = all_data.mid(i, next_separator - i);
            i = next_separator + 1;

            next_separator = all_data.indexOf(SEPARATOR, i);
            QByteArray msg3 = all_data.mid(i, next_separator - i);
            i = next_separator + 1;

            report(msg + msg2 + msg3);
        }
    }

    left_overs = all_data.mid(i);
}

void ClientWindow::report(QString str)
{
    ui->output->appendPlainText(str);
}

void ClientWindow::update_game_state(bool players_turn_x, Board board)
{
    turn_x = players_turn_x;
    board_widget->set_board(board);
}
