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
    if (cell == CELL_NONE)
    {
        qDebug() << "Cannot get piece from CELL_NONE";
        Q_ASSERT(false);
        return PIECE_TYPE_NONE;
    }

    return board_[(int) cell];
}

void BoardWidget::setPiece(Cell cell, PieceType piece)
{
    if (cell == CELL_NONE)
    {
        qDebug() << "Cannot set piece of CELL_NONE";
        Q_ASSERT(false);
        return;
    }

    board_[cell] = piece;
    repaint();
}

SimpleBoard BoardWidget::getBoard()
{
    return SimpleBoard(board_);
}

bool BoardWidget::gameOver()
{
    return winner() != PIECE_TYPE_NONE || !board_.contains(PIECE_TYPE_NONE);
}

void BoardWidget::clear()
{
    for (int i = 0; i < NUM_CELLS; i++)
    {
        board_[i] = PIECE_TYPE_NONE;
    }

    repaint();
}

PieceType BoardWidget::winner()
{
    QList<QList<PieceType>> cellsSet;
    cellsSet.append(top());
    cellsSet.append(midH());
    cellsSet.append(bot());
    cellsSet.append(left());
    cellsSet.append(midV());
    cellsSet.append(right());
    cellsSet.append(diagInc());
    cellsSet.append(diagDec());

    foreach (QList<PieceType> cells, cellsSet)
    {
        PieceType piece = containsOnly(cells);
        if (piece != PIECE_TYPE_NONE)
        {
            qDebug() << "Winner: " << piece;
            return piece;
        }
    }

    return PIECE_TYPE_NONE;
}

void BoardWidget::setActive(bool active)
{
    active_ = active;
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

QPoint BoardWidget::pointFromCell(Cell quad)
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

PieceType BoardWidget::containsOnly(QList<PieceType> cells)
{
    if (cells.contains(PIECE_TYPE_X))
    {
        if (!cells.contains(PIECE_TYPE_O) && !cells.contains(PIECE_TYPE_NONE))
        {
            return PIECE_TYPE_X;
        }
    }
    else if (cells.contains(PIECE_TYPE_O))
    {
        if (!cells.contains(PIECE_TYPE_X) && !cells.contains(PIECE_TYPE_NONE))
        {
            return PIECE_TYPE_O;
        }
    }

    return PIECE_TYPE_NONE;
}

QList<PieceType> BoardWidget::top()
{
    QList<PieceType> top;
    top.append(board_[CELL_TOP_LEFT]);
    top.append(board_[CELL_TOP_MID]);
    top.append(board_[CELL_TOP_RIGHT]);
    return top;
}

QList<PieceType> BoardWidget::midH()
{
    QList<PieceType> top;
    top.append(board_[CELL_MID_LEFT]);
    top.append(board_[CELL_MID_MID]);
    top.append(board_[CELL_MID_RIGHT]);
    return top;
}

QList<PieceType> BoardWidget::bot()
{
    QList<PieceType> top;
    top.append(board_[CELL_BOT_LEFT]);
    top.append(board_[CELL_BOT_MID]);
    top.append(board_[CELL_BOT_RIGHT]);
    return top;
}

QList<PieceType> BoardWidget::left()
{
    QList<PieceType> top;
    top.append(board_[CELL_TOP_LEFT]);
    top.append(board_[CELL_MID_LEFT]);
    top.append(board_[CELL_BOT_LEFT]);
    return top;
}

QList<PieceType> BoardWidget::midV()
{
    QList<PieceType> top;
    top.append(board_[CELL_TOP_MID]);
    top.append(board_[CELL_MID_MID]);
    top.append(board_[CELL_BOT_MID]);
    return top;
}

QList<PieceType> BoardWidget::right()
{
    QList<PieceType> top;
    top.append(board_[CELL_TOP_RIGHT]);
    top.append(board_[CELL_MID_RIGHT]);
    top.append(board_[CELL_BOT_RIGHT]);
    return top;
}

QList<PieceType> BoardWidget::diagDec()
{
    QList<PieceType> top;
    top.append(board_[CELL_TOP_LEFT]);
    top.append(board_[CELL_MID_MID]);
    top.append(board_[CELL_BOT_RIGHT]);
    return top;
}

QList<PieceType> BoardWidget::diagInc()
{
    QList<PieceType> top;
    top.append(board_[CELL_TOP_RIGHT]);
    top.append(board_[CELL_MID_MID]);
    top.append(board_[CELL_BOT_LEFT]);
    return top;
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

    if (!active_) painter.setOpacity(.25);

    // background/board
    QPixmap background(":/images/board.png");
    background = background.scaled(width(), height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, width(), height(), background);

    // pieces
    for (int cell_index = 0; cell_index < board_.size() ; cell_index++)
    {
        PieceType piece = board_[cell_index];

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
