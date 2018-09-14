#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

#define PLAYER_X "X"
#define PLAYER_O "O"

#include "data.h"

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = 0);
    ~BoardWidget();

    void set_board(QList<QString> * new_board);

signals:
    void board_clicked(Quad quad);

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

    QList<QString> * board;

};

#endif // BOARDWIDGET_H
