#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_restart_clicked();
    void on_button_start_clicked();

    void update_msg_label(QString msg);

private:
    Ui::MainWindow *ui;

    Game game;
};

#endif // MAINWINDOW_H
