#include "ClientMainWindow.h"
#include "ui_ClientMainWindow.h"

#include <QDebug>

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
    connect(gamePlayWidget_, SIGNAL(clickedValidCell(Cell)), SLOT(onGamePlayWidgetClickedValidCell(Cell)));
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

    // TODO
}

void ClientMainWindow::onSelectDifficultyWidgetClickedOk()
{
    gamePlayWidget_->clear();
    gamePlayWidget_->setActive(true);
    gamePlayWidget_->setTitle("Single Player Mode");
    gamePlayWidget_->setSubtitle("Good luck!");

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

void ClientMainWindow::onGamePlayWidgetClickedValidCell(Cell cell)
{
    if (!gamePlayWidget_->gameOver())
    {
        if (cell != CELL_NONE)
        {
            gamePlayWidget_->setPiece(cell, PIECE_TYPE_X);
            gamePlayWidget_->setActive(false);

            if (gamePlayWidget_->gameOver())
            {
                endGame(gamePlayWidget_->winner());
            }
            else
            {
                Cell aiMove = ai.getMove(gamePlayWidget_->getBoard(), PIECE_TYPE_O);
                gamePlayWidget_->setPiece(aiMove, PIECE_TYPE_O);

                if (gamePlayWidget_->gameOver())
                {
                    endGame(gamePlayWidget_->winner());
                }
                gamePlayWidget_->setActive(true);
            }
        }
    }
}

void ClientMainWindow::endGame(PieceType winner)
{
    QString winnerStr = "TIE!";
    if (winner == PIECE_TYPE_O) winnerStr = "O wins";
    if (winner == PIECE_TYPE_X) winnerStr = "X wins";
    gamePlayWidget_->setSubtitle(winnerStr);
}
