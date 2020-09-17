#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include "MyTCPClient.h"
#include "widgets/BoardWidget.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();

private slots:
    void on_button_start_clicked();
    void on_button_connect_clicked();
    void on_button_close_connection_clicked();
    void on_radio_one_player_clicked();
    void on_radio_multi_player_clicked();
    void onBoardClicked(Quad quad);

    void onGameInit(Player p1, Player p2);
    void onGameStateUpdated(Player player1, Player player2, BoardModel board);
    void onGameEnded(Player winner);

    void onGameUpdateMsgLabel(QString msg);
    void onTcpClientReport(QString msg);
    void onTcpClientReceivedData(QByteArray data);

private:
    Ui::ClientWindow *ui;
    BoardWidget * board_widget;
    Game game;

    MyTCPClient tcp_client;
    QString messageStream;

    void report(QString str);
    void processMessage(Message msg);

};

#endif // CLIENTWINDOW_H
