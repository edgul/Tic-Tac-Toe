#ifndef GAMEPLAYWIDGET_H
#define GAMEPLAYWIDGET_H

#include <QWidget>
#include "BoardWidget.h"

namespace Ui {
class GamePlayWidget;
}

class GamePlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GamePlayWidget(QWidget *parent = nullptr);
    ~GamePlayWidget();

signals:
    void clickedLeave();
    void clickedValidQuad(Quad quad);

private slots:
    void on_buttonLeave_clicked();
    void onBoardWidgetBoardClicked(Quad quad);

private:
    Ui::GamePlayWidget *ui;

    BoardWidget *boardWidget_;
};

#endif // GAMEPLAYWIDGET_H
