#include "BoardWidget.h"
#include "ui_BoardWidget.h"

#include <iostream>
#include <QPainter>
#include <QLine>
#include <QPoint>
#include <QFont>

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget)
{
    ui->setupUi(this);

}

BoardWidget::~BoardWidget()
{
    delete ui;
}

void BoardWidget::set_board(Board * new_board)
{
    board = new_board;

    repaint();
}

Quad BoardWidget::quadrant(QPoint p)
{
    Quad quadrant;

    if (is_top(p))
    {
        quadrant = QUAD_TOP_MID;

        if (is_left(p))
        {
            quadrant = QUAD_TOP_LEFT;
        }
        else if (is_right(p))
        {
            quadrant = QUAD_TOP_RIGHT;
        }
    }
    else if (is_bottom(p))
    {
        quadrant = QUAD_BOT_MID;

        if (is_left(p))
        {
            quadrant = QUAD_BOT_LEFT;
        }
        else if (is_right(p))
        {
            quadrant = QUAD_BOT_RIGHT;
        }
    }
    else // mid
    {
        quadrant = QUAD_MID_MID;

        if (is_left(p))
        {
            quadrant = QUAD_MID_LEFT;
        }
        else if (is_right(p))
        {
            quadrant = QUAD_MID_RIGHT;
        }
    }

    return quadrant;
}

QPoint BoardWidget::point_at_quad(Quad quad)
{
    int q_int = (int) quad;

    QPoint p;

    // set x
    if (q_int % 3 == 0)
    {
        p.setX(width()/6);
    }
    else if (q_int %3 == 1)
    {
        p.setX(width()/2);
    }
    else
    {
        p.setX(5*width()/6);
    }

    // set y
    if (q_int / 3 == 0)
    {
        p.setY(height()/6);
    }
    else if (q_int / 3 == 1)
    {
        p.setY(height()/2);
    }
    else
    {
        p.setY((5*height()/6));
    }

    return p;
}

bool BoardWidget::is_top(QPoint p)
{
    return p.y() < (height()/3);
}

bool BoardWidget::is_bottom(QPoint p)
{
    return p.y() > (2*height()/3);
}

bool BoardWidget::is_left(QPoint p)
{
    return p.x() < (width()/3);
}

bool BoardWidget::is_right(QPoint p)
{
    return p.x() > (2*width()/3);
}

void BoardWidget::mousePressEvent(QMouseEvent * event)
{
    QPoint p(event->x(), event->y());

    Quad quad = quadrant(p);

    emit board_clicked(quad);

    repaint();
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    int one_third_x  =     width()  / 3;
    int two_thirds_x = 2 * width()  / 3;
    int one_third_y  =     height() / 3;
    int two_thirds_y = 2 * height() / 3;

    QLine vertical_one_third(one_third_x, 0, one_third_x, height());
    QLine vertical_two_thirds(two_thirds_x, 0 , two_thirds_x, height());
    QLine horizontal_one_third(0, one_third_y, width(), one_third_y);
    QLine horizontal_two_thirds(0, two_thirds_y, width(), two_thirds_y);

    painter.drawLine(vertical_one_third);
    painter.drawLine(vertical_two_thirds);

    painter.drawLine(horizontal_one_third);
    painter.drawLine(horizontal_two_thirds);

    QFont font = QFont();
    font.setPointSize(14);
    painter.setFont(font);

    for (int quad_index = 0; quad_index < board->size() ; quad_index++)
    {
        QString letter = board->piece_at(quad_index);
        if (letter == EMPTY_CELL) letter = "";

        QPoint p = point_at_quad((Quad) quad_index);
        painter.drawText(p, letter);
    }

    QWidget::paintEvent(event);
    painter.end();
}
