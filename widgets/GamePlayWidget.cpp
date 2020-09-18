#include "GamePlayWidget.h"
#include "ui_GamePlayWidget.h"

#include <QDebug>

GamePlayWidget::GamePlayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePlayWidget)
{
    ui->setupUi(this);

    boardWidget_ = ui->boardWidget;
    connect(boardWidget_, SIGNAL(boardClicked(Cell)), SLOT(onBoardWidgetBoardClicked(Cell)));
}

GamePlayWidget::~GamePlayWidget()
{
    delete ui;
}

void GamePlayWidget::clear()
{
    boardWidget_->clear();
}

PieceType GamePlayWidget::getPiece(Cell cell)
{
    return boardWidget_->getPiece(cell);
}

void GamePlayWidget::setPiece(Cell cell, PieceType piece)
{
    boardWidget_->setPiece(cell, piece);
}

PieceType GamePlayWidget::winner()
{
    return boardWidget_->winner();
}

bool GamePlayWidget::gameOver()
{
    return boardWidget_->gameOver();
}

void GamePlayWidget::setActive(bool active)
{
    boardWidget_->setActive(active);
}

SimpleBoard GamePlayWidget::getBoard()
{
    return boardWidget_->simpleBoard();
}

void GamePlayWidget::setBoard(SimpleBoard board)
{
    boardWidget_->setBoard(board);
}

void GamePlayWidget::setTitle(const QString text)
{
    ui->labelTitle->setText(text);
}

void GamePlayWidget::setSubtitle(const QString text)
{
    ui->labelSubtitle->setText(text);
}

void GamePlayWidget::on_buttonLeave_clicked()
{
    emit clickedLeave();
}

void GamePlayWidget::onBoardWidgetBoardClicked(Cell cell)
{
    emit clickedValidCell(cell);
}
