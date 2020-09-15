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
    void setActive(bool active);
    void setBoard(Board new_board);
    void setWinner(PieceType pieceType);
    void setOverlayMessage(QString overlayMsg);

signals:
    void boardClicked(Quad quad);

private:
    Ui::BoardWidget *ui;

    Quad quadrant(QPoint p);
    QPoint point_at_quad(Quad quad);

    bool is_top(QPoint p);
    bool is_bottom(QPoint p);
    bool is_left(QPoint p);
    bool is_right(QPoint p);

    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);

    Board board;

    PieceType winner_;
    bool active_;
    QString overlayMessage_;

};

#endif // BOARDWIDGET_H
