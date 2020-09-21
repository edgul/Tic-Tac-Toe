#include "ClientMainWindow.h"
#include "ui_ClientMainWindow.h"

#include <QDebug>

ClientMainWindow::ClientMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow)
  , gameMode_(GAME_MODE_INIT)
{
    ui->setupUi(this);

    welcomeWidget_ = new WelcomeWidget(this);
    connect(welcomeWidget_, SIGNAL(clickedSinglePlayer()), SLOT(onWelcomeWidgetClickedSinglePlayer()));
    connect(welcomeWidget_, SIGNAL(clickedMultiPlayer()), SLOT(onWelcomeWidgetClickedMultiPlayer()));

    selectDifficultyWidget_ = new SelectDifficultyWidget(this);
    connect(selectDifficultyWidget_, SIGNAL(clickedOk()), SLOT(onSelectDifficultyWidgetClickedOk()));
    connect(selectDifficultyWidget_, SIGNAL(clickedCancel()), SLOT(onSelectDifficultyWidgetClickedCancel()));
    selectDifficultyWidget_->hide();

    gamePlayWidget_ = new GamePlayWidget(this);
    connect(gamePlayWidget_, SIGNAL(clickedLeave()), SLOT(onGamePlayWidgetClickedLeave()));
    connect(gamePlayWidget_, SIGNAL(clickedValidCell(Cell)), SLOT(onGamePlayWidgetClickedValidCell(Cell)));
    gamePlayWidget_->hide();

    connect(&tcp_client, SIGNAL(report(QString)), SLOT(onTcpClientReport(QString)));
    connect(&tcp_client, SIGNAL(receivedData(QByteArray)), SLOT(onTcpClientReceivedData(QByteArray)));
    connect(&tcp_client, SIGNAL(connected()), SLOT(onTcpClientConnected()));
    connect(&tcp_client, SIGNAL(disconnected()), SLOT(onTcpClientDisconnected()));
    connect(&tcp_client, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onTcpClientError(QAbstractSocket::SocketError)));
    ui->centralwidget = welcomeWidget_;
}

ClientMainWindow::~ClientMainWindow()
{
    // qDebug() << "Destroying client window";

    delete ui;
}

void ClientMainWindow::onWelcomeWidgetClickedSinglePlayer()
{
    ui->centralwidget->hide();
    ui->centralwidget = selectDifficultyWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onWelcomeWidgetClickedMultiPlayer()
{
    gamePlayWidget_->clear();
    gamePlayWidget_->setActive(false);
    gamePlayWidget_->setTitle("Multi Player Mode");

    gameMode_ = GAME_MODE_MULTI_CONNECTING;
    gamePlayWidget_->setSubtitle("Connecting...");
    tcp_client.connectToServer();

    ui->centralwidget->hide();
    ui->centralwidget = gamePlayWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onSelectDifficultyWidgetClickedOk()
{
    gameMode_ = GAME_MODE_SINGLE;
    gamePlayWidget_->clear();
    gamePlayWidget_->setActive(true);
    gamePlayWidget_->setTitle("Single Player Mode");
    gamePlayWidget_->setSubtitle("Good luck!");

    ui->centralwidget->hide();
    ui->centralwidget = gamePlayWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onSelectDifficultyWidgetClickedCancel()
{
    ui->centralwidget->hide();
    ui->centralwidget = welcomeWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onGamePlayWidgetClickedLeave()
{
    gameMode_ = GAME_MODE_INIT;

    tcp_client.disconnectFromServer();

    gamePlayWidget_->clear();
    gamePlayWidget_->setActive(false);

    ui->centralwidget->hide();
    ui->centralwidget = welcomeWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onGamePlayWidgetClickedValidCell(Cell cell)
{
    if (gameMode_ == GAME_MODE_SINGLE)
    {
        singlePlayerLogic(cell);
    }
    if (gameMode_ == GAME_MODE_MULTI_PLAYING)
    {
        // if is turn
        {
            tcp_client.sendMessage(Message::gamePlacePiece(cell));
        }
    }
}

void ClientMainWindow::onTcpClientReport(QString msg)
{
    qDebug() << "SERVER: " << msg;
}

void ClientMainWindow::onTcpClientReceivedData(QByteArray data)
{
    // qDebug() << "ClientMainWindow::onTcpClientReceivedData()";

    messageStream += QString::fromLatin1(data);

    int firstDelimiter;
    while ((firstDelimiter = messageStream.indexOf(DELIMITER)) != -1)
    {
        QString message = messageStream.mid(0, firstDelimiter);
        messageStream = messageStream.remove(0, firstDelimiter+4);

        processMessage(Message::messageFromString(message));
    }
}

void ClientMainWindow::onTcpClientConnected()
{
    // qDebug() << "ClientMainWindow::onTcpClientConnected()";

    gameMode_ = GAME_MODE_MULTI_WAITING;
    gamePlayWidget_->setSubtitle("Waiting for opponent...");

    tcp_client.sendMessage(Message::gameStart());
}

void ClientMainWindow::onTcpClientDisconnected()
{
    // qDebug() << "ClientMainWindow::onTcpClientDisconnected()";

    if (gameMode_ == GAME_MODE_MULTI_WAITING || gameMode_ == GAME_MODE_MULTI_PLAYING)
    {
        // qDebug() << "Connection appears to have failed";
        gameMode_ = GAME_MODE_INIT;
        ui->centralwidget->hide();
        ui->centralwidget = welcomeWidget_;
        ui->centralwidget->show();
    }
}

void ClientMainWindow::onTcpClientError(QAbstractSocket::SocketError err)
{
    // qDebug() << "ClientMainWindow::onTcpClientError()";

    if (gameMode_ == GAME_MODE_MULTI_CONNECTING)
    {
        qDebug() << "ERR: Couldn't connect to server: " << err;

        gameMode_ = GAME_MODE_INIT;
        ui->centralwidget->hide();
        ui->centralwidget = welcomeWidget_;
        ui->centralwidget->show();
    }
}

void ClientMainWindow::closeEvent(QCloseEvent *event)
{
    if (tcp_client.isConnected())
    {
        tcp_client.disconnectFromServer();
    }

    QWidget::closeEvent(event);
}

void ClientMainWindow::singlePlayerLogic(Cell cell)
{    
    if (!gamePlayWidget_->gameOver())
    {
        if (cell != CELL_NONE)
        {
            gamePlayWidget_->setPiece(cell, PIECE_TYPE_X);
            gamePlayWidget_->setActive(false);

            if (gamePlayWidget_->gameOver())
            {
                endGame(gamePlayWidget_->winner());
            }
            else
            {
                Cell aiMove = ai_.getMove(gamePlayWidget_->getBoard(),
                                         PIECE_TYPE_O,
                                         selectDifficultyWidget_->getDifficulty());
                gamePlayWidget_->setPiece(aiMove, PIECE_TYPE_O);

                if (gamePlayWidget_->gameOver())
                {
                    endGame(gamePlayWidget_->winner());
                }
                gamePlayWidget_->setActive(true);
            }
        }
    }
}

void ClientMainWindow::endGame(PieceType winner)
{
    QString winnerStr = "TIE!";
    if (winner == PIECE_TYPE_O) winnerStr = "O wins";
    if (winner == PIECE_TYPE_X) winnerStr = "X wins";
    gamePlayWidget_->setSubtitle(winnerStr);
}

void ClientMainWindow::report(QString str)
{
    qDebug() << str;

}

void ClientMainWindow::processMessage(Message msg)
{
    // qDebug() << "ClientMainWindow::processMessage()";

    if (msg.getFunction() == FUNCTION_GAME_INIT)
    {
        qDebug() << "Processing: Game init";
        gameMode_ = GAME_MODE_MULTI_PLAYING;
        gamePlayWidget_->clear();
        gamePlayWidget_->setActive(true);
        multiPlayerPiece_ = msg.getPieceType();

        if (multiPlayerPiece_ == PIECE_TYPE_X)
        {
            gamePlayWidget_->setSubtitle("You're X");
        }
        else
        {
            gamePlayWidget_->setSubtitle("You're O");
        }
    }
    else if (msg.getFunction() == FUNCTION_GAME_UPDATE)
    {
        qDebug() << "Processing: Game update";

        gamePlayWidget_->setBoard(msg.getSimpleBoard());
    }
    else if (msg.getFunction() == FUNCTION_GAME_END)
    {
        qDebug() << "Processing: Game end";

        PieceType winnerPiece = msg.getPieceType();
        gamePlayWidget_->setActive(false);

        QString msg;
        if      (winnerPiece == PIECE_TYPE_X) msg = "X Wins!";
        else if (winnerPiece == PIECE_TYPE_O) msg = "O Wins!";
        else                                  msg = "Tie!";
        gamePlayWidget_->setSubtitle(msg);
    }
}
