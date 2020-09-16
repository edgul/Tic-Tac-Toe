#ifndef SELECTDIFFICULTYWIDGET_H
#define SELECTDIFFICULTYWIDGET_H

#include <QWidget>

namespace Ui {
class SelectDifficultyWidget;
}

class SelectDifficultyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectDifficultyWidget(QWidget *parent = nullptr);
    ~SelectDifficultyWidget();

    enum AiDifficulty { AI_DIFFICULTY_EASY, AI_DIFFICULTY_MED, AI_DIFFICULTY_HARD, AI_DIFFICULTY_NONE };
    AiDifficulty getDifficulty();

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
