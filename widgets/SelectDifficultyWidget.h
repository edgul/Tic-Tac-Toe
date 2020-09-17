#ifndef SELECTDIFFICULTYWIDGET_H
#define SELECTDIFFICULTYWIDGET_H

#include <QWidget>
#include "data/data.h"

namespace Ui {
class SelectDifficultyWidget;
}

class SelectDifficultyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectDifficultyWidget(QWidget *parent = nullptr);
    ~SelectDifficultyWidget();

    Difficulty getDifficulty();

private slots:
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

signals:
    void clickedOk();
    void clickedCancel();

private:
    Ui::SelectDifficultyWidget *ui;
};

#endif // SELECTDIFFICULTYWIDGET_H
