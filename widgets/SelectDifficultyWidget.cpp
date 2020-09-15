#include "SelectDifficultyWidget.h"
#include "ui_SelectDifficultyWidget.h"

SelectDifficultyWidget::SelectDifficultyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectDifficultyWidget)
{
    ui->setupUi(this);
}

SelectDifficultyWidget::~SelectDifficultyWidget()
{
    delete ui;
}

void SelectDifficultyWidget::on_pushButtonOk_clicked()
{
    emit clickedOk();
}

void SelectDifficultyWidget::on_pushButtonCancel_clicked()
{
    emit clickedCancel();
}
