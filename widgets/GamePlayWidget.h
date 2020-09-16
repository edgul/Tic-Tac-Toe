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

    void clear();
    PieceType getPiece(Cell quad);
    void setPiece(Cell quad, PieceType piece);
    PieceType winner();
    bool gameOver();
    void setActive(bool active);
    SimpleBoard getBoard();

    void setTitle(const QString text);
    void setSubtitle(const QString text);
signals:
    void clickedLeave();
    void clickedValidCell(Cell quad);

private slots:
    void on_buttonLeave_clicked();
    void onBoardWidgetBoardClicked(Cell cell);

private:
    Ui::GamePlayWidget *ui;

    BoardWidget *boardWidget_;
};

#endif // GAMEPLAYWIDGET_H
