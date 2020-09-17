#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include "data/data.h"
#include "data/BoardModel.h"

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = 0);
    ~BoardWidget();

    void clear();
    PieceType getPiece(Cell cell);
    void setPiece(Cell cell, PieceType piece);
    SimpleBoard simpleBoard();
    bool gameOver();
    PieceType winner();

    void setActive(bool active);

    // TODO: remove
    void setOverlayMessage(const QString text) {}
    void setBoard(BoardModel board) {}
    void setWinner(PieceType piece) {}

signals:
    void boardClicked(Cell quad);

protected:
    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);

private:
    Ui::BoardWidget *ui;

    bool active_;
    BoardModel boardModel_;

    Cell cellFromPoint(QPoint p);
    QPoint pointFromCell(Cell quad);

    // determine where point is
    bool is_top(QPoint p);
    bool is_bottom(QPoint p);
    bool is_left(QPoint p);
    bool is_right(QPoint p);

};

#endif // BOARDWIDGET_H
