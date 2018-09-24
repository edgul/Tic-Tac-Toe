#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game.set_board(ui->board_widget);

    connect(&game, SIGNAL(update_msg_label(QString)), this, SLOT(update_msg_label(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_start_clicked()
{

    if (ui->radio_multi_player->isChecked())
    {
        game.start_multiplayer();
    }
    else
    {
        Difficulty difficulty = DIFFICULTY_EASY;
        if (ui->radio_difficulty_medium->isChecked()) difficulty = DIFFICULTY_MEDIUM;
        if (ui->radio_difficulty_hard->isChecked()) difficulty = DIFFICULTY_HARD;

        game.start_one_player(difficulty);
    }
}

void MainWindow::update_msg_label(QString msg)
{
    ui->label_msg->setText(msg);
}

void MainWindow::on_button_connect_clicked()
{
    tcp_client.connect_to_server();
}

void MainWindow::on_button_send_data_clicked()
{
    tcp_client.send(QString("Hello\n"));
}

void MainWindow::on_button_close_connection_clicked()
{
    tcp_client.close();
}

void MainWindow::on_radio_one_player_clicked()
{
    ui->frame_difficulty->setEnabled(true);
}

void MainWindow::on_radio_multi_player_clicked()
{
    ui->frame_difficulty->setEnabled(false);
}
