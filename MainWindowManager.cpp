#include "MainWindowManager.h"
#include "ui_MainWindowManager.h"

#include "MainWindow.h"

MainWindowManager::MainWindowManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindowManager)
{
    ui->setupUi(this);

}

MainWindowManager::~MainWindowManager()
{
    delete ui;
}

void MainWindowManager::on_button_new_main_window_clicked()
{
    MainWindow * mw = new MainWindow();
    mw->show();
}
