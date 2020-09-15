#include "BoardWidget.h"
#include "ui_BoardWidget.h"

#include <iostream>
#include <QPainter>
#include <QLine>
#include <QPoint>
#include <QFont>

#include <QDebug>


BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardWidget),
    winner_(PIECE_TYPE_NONE),
    active_(false),
    overlayMessage_("")
{
    ui->setupUi(this);

}

BoardWidget::~BoardWidget()
{
    delete ui;
}

void BoardWidget::clear()
{
    board.clear();
    winner_ = PIECE_TYPE_NONE;
    overlayMessage_ = "";
    repaint();
}

void BoardWidget::setActive(bool active)
{
    active_ = active;
    repaint();
}

void BoardWidget::setBoard(Board new_board)
{
    board = new_board;
    repaint();
}

void BoardWidget::setWinner(PieceType pieceType)
{
    winner_ = pieceType;
    repaint();
}

void BoardWidget::setOverlayMessage(QString overlayMsg)
{
    overlayMessage_ = overlayMsg;
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
    emit boardClicked(quad);
    repaint();
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    if (!active_) painter.setOpacity(.25);

    // background/board
    QPixmap background(":/images/board.png");
    background = background.scaled(width(), height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0,0, width(), height(), background);

    // pieces
    for (int quad_index = 0; quad_index < board.size() ; quad_index++)
    {
        QString letter = board.piece_at(quad_index);
        if (letter != EMPTY_CELL)
        {
            QString png = ":/images/o.png";
            if (letter == PLAYER_X) png = ":/images/x.png";

            int pieceWidth = 40;
            int pieceHeight = 40;
            QPoint p = point_at_quad((Quad) quad_index);
            QPixmap piecePixmap(png);
            piecePixmap = piecePixmap.scaled(pieceWidth, pieceHeight,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(p.x()-pieceWidth/2, p.y()-pieceHeight/2, pieceWidth, pieceHeight, piecePixmap);
        }
    }

    // game over message
    if (overlayMessage_ != "")
    {
        QFont font = QFont();
        font.setPointSize(14);
        painter.setFont(font);
        painter.setOpacity(1);
        painter.setPen(Qt::red);
        painter.drawText(QPoint(width()/2, height()/2), overlayMessage_);
    }

    QWidget::paintEvent(event);
    painter.end();
}
