#include "ClientWindow.h"
#include "ui_ClientWindow.h"

#include "data/Message.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    board_widget = ui->board_widget;

    bool multiPlayer = true;
    ui->radio_multi_player->setChecked(multiPlayer);
    ui->frame_difficulty->setEnabled(!multiPlayer);

    connect(board_widget, SIGNAL(boardClicked(Quad)), SLOT(onBoardClicked(Quad)));

    connect(&tcp_client, SIGNAL(report(QString)), SLOT(onTcpClientReport(QString)));
    connect(&tcp_client, SIGNAL(receivedData(QByteArray)), SLOT(onTcpClientReceivedData(QByteArray)));
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_button_start_clicked()
{
    if (ui->radio_multi_player->isChecked())
    {
        board_widget->clear();
        board_widget->setOverlayMessage("Waiting for opponent...");

        Message msg(TARGET_GAME, FUNCTION_GAME_START);
        tcp_client.sendMessage(msg);
    }
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

    board_widget->clear();
    board_widget->setActive(false);
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
    if (tcp_client.isConnected())
    {
        Message msg(TARGET_GAME, FUNCTION_GAME_PLACE, quad);
        tcp_client.sendMessage(msg);
    }
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
    if (msg.getFunction() == FUNCTION_GAME_INIT)
    {
        board_widget->clear();
        board_widget->setActive(true);
    }
    else if (msg.getFunction() == FUNCTION_GAME_UPDATE)
    {
        BoardModel board;
        board.set_board_from_string(msg.getBoardStr());
        board_widget->setBoard(board);
    }
    else if (msg.getFunction() == FUNCTION_GAME_END)
    {
        PieceType winnerPiece = msg.getPieceType();
        board_widget->setActive(false);
        board_widget->setWinner(winnerPiece);

        QString msg;
        if      (winnerPiece == PIECE_TYPE_X) msg = "X Wins!";
        else if (winnerPiece == PIECE_TYPE_O) msg = "O Wins!";
        else                                  msg = "Tie!";
        board_widget->setOverlayMessage(msg);
    }

}

