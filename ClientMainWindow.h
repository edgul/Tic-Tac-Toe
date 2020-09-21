#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include "AI.h"
#include "TcpClient.h"
#include "widgets/WelcomeWidget.h"
#include "widgets/SelectDifficultyWidget.h"
#include "widgets/GamePlayWidget.h"

namespace Ui {
class ClientMainWindow;
}

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QWidget *parent = nullptr);
    ~ClientMainWindow();

private slots:
    void onWelcomeWidgetClickedSinglePlayer();
    void onWelcomeWidgetClickedMultiPlayer();

    void onSelectDifficultyWidgetClickedOk();
    void onSelectDifficultyWidgetClickedCancel();

    void onGamePlayWidgetClickedLeave();
    void onGamePlayWidgetClickedValidCell(Cell cell);

    void onTcpClientReport(QString msg);
    void onTcpClientReceivedData(QByteArray data);
    void onTcpClientConnected();
    void onTcpClientDisconnected();
    void onTcpClientError(QAbstractSocket::SocketError err);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ClientMainWindow *ui;

    enum GameMode { GAME_MODE_INIT,
                    GAME_MODE_SINGLE,
                    GAME_MODE_MULTI_CONNECTING,
                    GAME_MODE_MULTI_WAITING,
                    GAME_MODE_MULTI_PLAYING };
    GameMode gameMode_;

    WelcomeWidget *welcomeWidget_;
    SelectDifficultyWidget *selectDifficultyWidget_;
    GamePlayWidget *gamePlayWidget_;
    AI ai_;

    TcpClient tcp_client;
    QString messageStream;

    PieceType multiPlayerPiece_;

    void singlePlayerLogic(Cell cell);
    void endGame(PieceType winner);

    void report(QString str);
    void processMessage(Message msg);
};

#endif // CLIENTMAINWINDOW_H
