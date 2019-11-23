#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include "MyTCPClient.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();

    void set_player(bool x);

private slots:
    void on_button_start_clicked();
    void on_button_connect_clicked();
    void on_button_close_connection_clicked();
    void on_radio_one_player_clicked();
    void on_radio_multi_player_clicked();
    void onBoardClicked(Quad quad);

    void onGameUpdateMsgLabel(QString msg);
    void onTcpClientReport(QString msg);
    void onTcpClientReceivedData(QByteArray data);

private:
    Ui::ClientWindow *ui;

    void report(QString str);
    void update_game_state(bool players_turn_x, Board board);

    bool piece_x;
    bool turn_x;
    Game game;
    BoardWidget * board_widget;

    MyTCPClient tcp_client;
    QByteArray left_overs;

};

#endif // CLIENTWINDOW_H
