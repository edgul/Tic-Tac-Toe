#include "ClientWindow.h"
#include "ui_ClientWindow.h"

#include "Message.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    board_widget = ui->board_widget;

    ui->radio_multi_player->setChecked(true);

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
        Message msg(TARGET_GAME, FUNCTION_GAME_START);
        tcp_client.sendMessage(msg);
    }
    else
    {
        Difficulty difficulty = DIFFICULTY_EASY;
        if (ui->radio_difficulty_medium->isChecked()) difficulty = DIFFICULTY_MEDIUM;
        if (ui->radio_difficulty_hard->isChecked()) difficulty = DIFFICULTY_HARD;

        game.startSinglePlayer(difficulty);
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
    tcp_client.connectToServer();
}

void ClientWindow::on_button_close_connection_clicked()
{
    tcp_client.disconnectFromServer();
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
    Message msg(TARGET_GAME, FUNCTION_GAME_PLACE, quad);
    tcp_client.sendMessage(msg);
}

void ClientWindow::onTcpClientReceivedData(QByteArray data)
{
    messageStream += QString::fromLatin1(data);

    int firstDelimiter;
    while ((firstDelimiter = messageStream.indexOf(DELIMITER)) != -1)
    {
        QString message = messageStream.mid(0, firstDelimiter);
        messageStream = messageStream.remove(0, firstDelimiter+4);

        Message msg(message);
        processMessage(msg);
    }
}

void ClientWindow::report(QString str)
{
    ui->output->appendPlainText(str);
}

void ClientWindow::processMessage(Message msg)
{
    if (msg.getFunction() == FUNCTION_HANDSHAKE_RESPONSE)
    {
        qDebug() << "TcpClient::Handshake Response -- undetermined result";
    }
    else if (msg.getFunction() == FUNCTION_GAME_INIT)
    {

    }
    else if (msg.getFunction() == FUNCTION_GAME_UPDATE)
    {
        // TODO: improve this
        Board board;
        board.set_board_from_string(msg.getBoardStr());
        board_widget->set_board(board);
    }
    else if (msg.getFunction() == FUNCTION_GAME_END)
    {

    }
    else if (msg.getFunction() == FUNCTION_HELLO_WORLD) // o cutoff
    {
        qDebug() << "TCPClient::Hello World";

        report("Client received hello world");
    }
}

