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

SelectDifficultyWidget::AiDifficulty SelectDifficultyWidget::getDifficulty()
{
    if (ui->radioButtonEasy->isChecked())
    {
        return AI_DIFFICULTY_EASY;
    }
    else if (ui->radioButtonMedium->isChecked())
    {
        return AI_DIFFICULTY_MED;
    }
    else if (ui->radioButtonHard->isChecked())
    {
        return AI_DIFFICULTY_HARD;
    }
    else
    {
        qDebug() << "Could not get difficulty from SelectDifficultyWidget";
        Q_ASSERT(false);
        return AI_DIFFICULTY_NONE;
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
