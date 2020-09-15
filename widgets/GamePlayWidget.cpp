#include "GamePlayWidget.h"
#include "ui_GamePlayWidget.h"

GamePlayWidget::GamePlayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamePlayWidget)
{
    ui->setupUi(this);

    boardWidget_ = ui->boardWidget;
    connect(boardWidget_, SIGNAL(boardClicked(Quad)), SLOT(onBoardWidgetBoardClicked(Quad)));
}

GamePlayWidget::~GamePlayWidget()
{
    delete ui;
}

void GamePlayWidget::on_buttonLeave_clicked()
{
    emit clickedLeave();
}

void GamePlayWidget::onBoardWidgetBoardClicked(Quad quad)
{
    // TODO filter clicks
    emit clickedValidQuad(quad);
}
