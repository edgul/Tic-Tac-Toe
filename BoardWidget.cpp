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

    for (int i = 0; i < 9; i++)
    {
        board.append("");
    }

    // define win sets
    QList<Quad> h_top = QList<Quad>() << QUAD_TOP_LEFT << QUAD_TOP_MID << QUAD_TOP_RIGHT;
    QList<Quad> h_mid = QList<Quad>() << QUAD_MID_LEFT << QUAD_MID_MID << QUAD_MID_RIGHT;
    QList<Quad> h_bot = QList<Quad>() << QUAD_BOT_LEFT << QUAD_BOT_MID << QUAD_BOT_RIGHT;

    QList<Quad> v_left = QList<Quad>() << QUAD_TOP_LEFT  << QUAD_MID_LEFT << QUAD_BOT_LEFT;
    QList<Quad> v_mid  = QList<Quad>() << QUAD_TOP_MID   << QUAD_MID_MID << QUAD_BOT_MID;
    QList<Quad> v_right =QList<Quad>() << QUAD_TOP_RIGHT << QUAD_MID_RIGHT << QUAD_BOT_RIGHT;

    QList<Quad> d_r    = QList<Quad>() << QUAD_BOT_LEFT << QUAD_MID_MID << QUAD_TOP_RIGHT;
    QList<Quad> d_l    = QList<Quad>() << QUAD_BOT_RIGHT << QUAD_MID_MID << QUAD_TOP_LEFT;

    wins.append(h_top);
    wins.append(h_mid);
    wins.append(h_bot);

    wins.append(v_left);
    wins.append(v_mid);
    wins.append(v_right);

    wins.append(d_r);
    wins.append(d_l);
}

BoardWidget::~BoardWidget()
{
    delete ui;
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

void BoardWidget::clear()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = "";
    }

    repaint();
}

void BoardWidget::place_x(Quad q)
{
    int q_int = (int) q;
    board[q_int] = PLAYER_X;
}

void BoardWidget::place_o(Quad q)
{
    int q_int = (int) q;
    board[q_int] = PLAYER_O;
}

bool BoardWidget::full()
{
    bool full = true;

    foreach (QString s, board)
    {
        if (s == "")
        {
            full = false;
            break;
        }
    }

    return full;
}

bool BoardWidget::win_exists()
{
    bool a_win = false;

    foreach (QList<Quad> win, wins)
    {
        bool these_quads = true;

        // check x win
        foreach(Quad quad, win)
        {
            if (!quads_with_x().contains(quad))
            {
                these_quads = false;
            }
        }

        these_quads = true;

        // check o win
        foreach(Quad quad, win)
        {
            if (!quads_with_o().contains(quad))
            {
                these_quads = false;
            }
        }


        if (these_quads)
        {
            a_win = true;
            break;
        }
    }

    return a_win;

}

QString BoardWidget::winner()
{
    QString winner = "";

    foreach (QList<Quad> win, wins)
    {
        bool these_quads_win = true;

        foreach(Quad quad, win)
        {
            if (!quads_with_x().contains(quad))
            {
                these_quads_win = false;
            }
        }

        if (these_quads_win)
        {
            winner = PLAYER_X;
            break;
        }

        these_quads_win = true;

        foreach(Quad quad, win)
        {
            if (!quads_with_o().contains(quad))
            {
                these_quads_win = false;
            }
        }

        if (these_quads_win)
        {
            winner = PLAYER_O;
            break;
        }
    }

    return winner;
}

bool BoardWidget::quad_empty(Quad quad)
{
    bool empty = false;
    if (board[quad] == "") empty = true;

    return empty;
}

QList<Quad> BoardWidget::quads_with_x()
{
    QList<Quad> quads;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] == PLAYER_X)
        {
            quads.append( (Quad) i);
        }
    }

    return quads;
}

QList<Quad> BoardWidget::quads_with_o()
{
    QList<Quad> quads;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] == PLAYER_O)
        {
            quads.append( (Quad) i);
        }
    }

    return quads;
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

    for (int quad = 0; quad < board.length(); quad++)
    {
        QString letter = board[quad];
        QPoint p = point_at_quad((Quad) quad);
        painter.drawText(p, letter);
    }

    QWidget::paintEvent(event);
    painter.end();
}
