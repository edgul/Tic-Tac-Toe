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

void MainWindow::on_button_restart_clicked()
{
    game.start();
}

void MainWindow::on_button_start_clicked()
{
    game.start();
}

void MainWindow::update_msg_label(QString msg)
{
    ui->label_msg->setText(msg);
}
