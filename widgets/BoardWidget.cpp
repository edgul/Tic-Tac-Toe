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
    active_(false)
{
    ui->setupUi(this);

}

BoardWidget::~BoardWidget()
{
    delete ui;
}

PieceType BoardWidget::getPiece(Cell cell)
{
    return boardModel_.getPiece(cell);
}

void BoardWidget::setPiece(Cell cell, PieceType piece)
{
    boardModel_.setPiece(cell, piece);
    repaint();
}

SimpleBoard BoardWidget::simpleBoard()
{
    return boardModel_.simpleBoard();
}

bool BoardWidget::gameOver()
{
    return boardModel_.gameOver();
}

void BoardWidget::clear()
{
    boardModel_.clearPieces();
    repaint();
}

PieceType BoardWidget::winner()
{
    return boardModel_.winnerPiece();
}

void BoardWidget::setActive(bool active)
{
    active_ = active;
    repaint();
}

void BoardWidget::setBoard(SimpleBoard board)
{
    boardModel_ = BoardModel(board);
    repaint();
}

Cell BoardWidget::cellFromPoint(QPoint p)
{
    Cell cell = CELL_NONE;

    if (is_top(p))
    {
        cell = CELL_TOP_MID;

        if (is_left(p))
        {
            cell = CELL_TOP_LEFT;
        }
        else if (is_right(p))
        {
            cell = CELL_TOP_RIGHT;
        }
    }
    else if (is_bottom(p))
    {
        cell = CELL_BOT_MID;

        if (is_left(p))
        {
            cell = CELL_BOT_LEFT;
        }
        else if (is_right(p))
        {
            cell = CELL_BOT_RIGHT;
        }
    }
    else // mid
    {
        cell = CELL_MID_MID;

        if (is_left(p))
        {
            cell = CELL_MID_LEFT;
        }
        else if (is_right(p))
        {
            cell = CELL_MID_RIGHT;
        }
    }

    return cell;
}

QPoint BoardWidget::pointFromCell(Cell cell)
{
    int c_int = (int) cell;

    QPoint p;

    // set x
    if (c_int % 3 == 0)
    {
        p.setX(width()/6);
    }
    else if (c_int %3 == 1)
    {
        p.setX(width()/2);
    }
    else
    {
        p.setX(5*width()/6);
    }

    // set y
    if (c_int / 3 == 0)
    {
        p.setY(height()/6);
    }
    else if (c_int / 3 == 1)
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
    if (active_)
    {
        QPoint p(event->x(), event->y());
        Cell cell = cellFromPoint(p);
        if (getPiece(cell) == PIECE_TYPE_NONE)
        {
            emit boardClicked(cell);
        }
    }
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    // if (!active_) painter.setOpacity(.25);

    // background/board
    QPixmap background(":/images/board.png");
    background = background.scaled(width(), height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, width(), height(), background);

    // pieces
    for (int cell_index = 0; cell_index < NUM_CELLS ; cell_index++)
    {
        PieceType piece = boardModel_.getPiece((Cell) cell_index);

        if (piece != PIECE_TYPE_NONE)
        {
            QString png = ":/images/o.png";
            if (piece == PIECE_TYPE_X) png = ":/images/x.png";
            int pieceWidth = 40;
            int pieceHeight = 40;
            QPoint p = pointFromCell((Cell) cell_index);
            QPixmap piecePixmap(png);
            piecePixmap = piecePixmap.scaled(pieceWidth, pieceHeight,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            painter.drawPixmap(p.x()-pieceWidth/2, p.y()-pieceHeight/2, pieceWidth, pieceHeight, piecePixmap);
        }
    }

    QWidget::paintEvent(event);
    painter.end();
}
