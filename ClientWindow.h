#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "Game.h"
#include "Player.h"

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

    void update_msg_label(QString msg);
    void update_output(QString msg);

    // client/server
    void on_button_connect_clicked();
    void on_button_close_connection_clicked();

    void on_radio_one_player_clicked();
    void on_radio_multi_player_clicked();

private:
    Ui::ClientWindow *ui;

    bool player_x;

    Game game;

    Player player;
};

#endif // CLIENTWINDOW_H
