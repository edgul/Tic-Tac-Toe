#include "ClientWindow.h"
#include "ui_ClientWindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    game.init_board(ui->board_widget);
    player.init_board(ui->board_widget);

    connect(&game, SIGNAL(update_msg_label(QString)), this, SLOT(update_msg_label(QString)));

    connect(&player, SIGNAL(report(QString)), this, SLOT(update_output(QString)));
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::set_player(bool x)
{
    player.set_piece(x);
}

void ClientWindow::on_button_start_clicked()
{

    if (ui->radio_multi_player->isChecked())
    {
        // game.start_multiplayer();
    }
    else
    {
        Difficulty difficulty = DIFFICULTY_EASY;
        if (ui->radio_difficulty_medium->isChecked()) difficulty = DIFFICULTY_MEDIUM;
        if (ui->radio_difficulty_hard->isChecked()) difficulty = DIFFICULTY_HARD;

        game.start_one_player(difficulty);
    }
}

void ClientWindow::update_msg_label(QString msg)
{
    ui->label_msg->setText(msg);
}

void ClientWindow::update_output(QString msg)
{
    ui->output->appendPlainText(msg);
}

void ClientWindow::on_button_connect_clicked()
{
    player.connect_to_server();
}

void ClientWindow::on_button_close_connection_clicked()
{
    player.close_connection();
}

void ClientWindow::on_radio_one_player_clicked()
{
    ui->frame_difficulty->setEnabled(true);
}

void ClientWindow::on_radio_multi_player_clicked()
{
    ui->frame_difficulty->setEnabled(false);
}
