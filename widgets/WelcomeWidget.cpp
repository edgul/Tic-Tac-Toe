#include "WelcomeWidget.h"
#include "ui_WelcomeWidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::on_buttonSinglePlayer_clicked()
{
    emit clickedSinglePlayer();
}

void WelcomeWidget::on_buttonMultiPlayer_clicked()
{
    emit clickedMultiPlayer();
}
