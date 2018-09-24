#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include "MyTCPClient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MyTCPClient tcp_client;

private slots:
    void on_button_start_clicked();

    void update_msg_label(QString msg);

    // client/server
    void on_button_connect_clicked();
    void on_button_send_data_clicked();
    void on_button_close_connection_clicked();

    void on_radio_one_player_clicked();
    void on_radio_multi_player_clicked();

private:
    Ui::MainWindow *ui;

    Game game;
};

#endif // MAINWINDOW_H
