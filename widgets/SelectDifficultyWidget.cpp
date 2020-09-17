#include "SelectDifficultyWidget.h"
#include "ui_SelectDifficultyWidget.h"

#include <QDebug>

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

Difficulty SelectDifficultyWidget::getDifficulty()
{
    if (ui->radioButtonEasy->isChecked())
    {
        return DIFFICULTY_EASY;
    }
    else if (ui->radioButtonMedium->isChecked())
    {
        return DIFFICULTY_MEDIUM;
    }
    else if (ui->radioButtonHard->isChecked())
    {
        return DIFFICULTY_HARD;
    }
    else
    {
        qDebug() << "Could not get difficulty from SelectDifficultyWidget";
        Q_ASSERT(false);
        return DIFFICULTY_NONE;
    }
}

void SelectDifficultyWidget::on_pushButtonOk_clicked()
{
    emit clickedOk();
}

void SelectDifficultyWidget::on_pushButtonCancel_clicked()
{
    emit clickedCancel();
}
