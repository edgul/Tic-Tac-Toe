#include "ClientMainWindow.h"
#include "ui_ClientMainWindow.h"


ClientMainWindow::ClientMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);

    welcomeWidget_ = new WelcomeWidget(this);
    connect(welcomeWidget_, SIGNAL(clickedSinglePlayer()), SLOT(onWelcomeWidgetClickedSinglePlayer()));
    connect(welcomeWidget_, SIGNAL(clickedMultiPlayer()), SLOT(onWelcomeWidgetClickedMultiPlayer()));

    selectDifficultyWidget_ = new SelectDifficultyWidget(this);
    connect(selectDifficultyWidget_, SIGNAL(clickedOk()), SLOT(onSelectDifficultyWidgetClickedOk()));
    connect(selectDifficultyWidget_, SIGNAL(clickedCancel()), SLOT(onSelectDifficultyWidgetClickedCancel()));
    selectDifficultyWidget_->hide();

    gamePlayWidget_ = new GamePlayWidget(this);
    connect(gamePlayWidget_, SIGNAL(clickedLeave()), SLOT(onGamePlayWidgetClickedLeave()));
    gamePlayWidget_->hide();

    ui->centralwidget = welcomeWidget_;
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}

void ClientMainWindow::onWelcomeWidgetClickedSinglePlayer()
{
    ui->centralwidget->hide();
    ui->centralwidget = selectDifficultyWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onWelcomeWidgetClickedMultiPlayer()
{
    ui->centralwidget->hide();
    ui->centralwidget = gamePlayWidget_;
    ui->centralwidget->show();

}

void ClientMainWindow::onSelectDifficultyWidgetClickedOk()
{
    ui->centralwidget->hide();
    ui->centralwidget = gamePlayWidget_;
    ui->centralwidget->show();

}

void ClientMainWindow::onSelectDifficultyWidgetClickedCancel()
{
    ui->centralwidget->hide();
    ui->centralwidget = welcomeWidget_;
    ui->centralwidget->show();

}

void ClientMainWindow::onGamePlayWidgetClickedLeave()
{
    ui->centralwidget->hide();
    ui->centralwidget = welcomeWidget_;
    ui->centralwidget->show();
}

void ClientMainWindow::onGamePlayWidgetClickedValidQuad(Quad quad)
{

}
