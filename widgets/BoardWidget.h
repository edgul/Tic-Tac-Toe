#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

#include "data.h"
#include "Board.h"

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
    SimpleBoard getBoard();
    bool gameOver();

    PieceType winner();
    void setActive(bool active);

    // TODO: remove
    void setOverlayMessage(const QString text) {}
    void setBoard(Board board) {}
    void setWinner(PieceType piece) {}

signals:
    void boardClicked(Cell quad);

protected:
    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);

private:
    Ui::BoardWidget *ui;

    bool active_;
    QList<PieceType> board_ = { PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                                PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                                PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE
                              };

    Cell cellFromPoint(QPoint p);
    QPoint pointFromCell(Cell quad);

    // determine where point is
    bool is_top(QPoint p);
    bool is_bottom(QPoint p);
    bool is_left(QPoint p);
    bool is_right(QPoint p);

    PieceType containsOnly(QList<PieceType> cells);
    QList<PieceType> top();
    QList<PieceType> midH();
    QList<PieceType> bot();
    QList<PieceType> left();
    QList<PieceType> midV();
    QList<PieceType> right();
    QList<PieceType> diagDec();
    QList<PieceType> diagInc();
};

#endif // BOARDWIDGET_H
