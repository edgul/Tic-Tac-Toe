#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

#define PLAYER_X "X"
#define PLAYER_O "O"

namespace Ui {
class BoardWidget;
}

enum Quad
{
    QUAD_TOP_LEFT = 0,
    QUAD_TOP_MID   ,
    QUAD_TOP_RIGHT ,
    QUAD_MID_LEFT  ,
    QUAD_MID_MID   ,
    QUAD_MID_RIGHT ,
    QUAD_BOT_LEFT  ,
    QUAD_BOT_MID   ,
    QUAD_BOT_RIGHT
};

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = 0);
    ~BoardWidget();

    void clear();
    void place_x(Quad q);
    void place_o(Quad q);

    bool full();

    // might go in game
    bool win_exists();
    QString winner();

    bool quad_empty(Quad quad);

signals:
    void board_clicked(Quad quad);

private:
    Ui::BoardWidget *ui;

    QList<Quad> quads_with_x();
    QList<Quad> quads_with_o();

    Quad quadrant(QPoint p);
    QPoint point_at_quad(Quad quad);

    bool is_top(QPoint p);
    bool is_bottom(QPoint p);
    bool is_left(QPoint p);
    bool is_right(QPoint p);

    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent * event);

    QList<QString> board;
    QList<QList<Quad>> wins;
};

#endif // BOARDWIDGET_H
