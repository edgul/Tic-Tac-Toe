#include "data/BoardModel.h"

#include <QDebug>

BoardModel::BoardModel()
{

}

BoardModel::BoardModel(SimpleBoard sBoard) :
    board_(sBoard.board)
{

}

QString BoardModel::toString()
{
    return board.join("");
}

void BoardModel::set_board_from_string(QString b_string)
{
    QList<QString> list;
    foreach (QString s, b_string)
    {
        list.append(s);
    }

    board = list;
}

PieceType BoardModel::winnerPiece()
{
    QList<QList<PieceType>> cellsSet;
    cellsSet.append(top()    .values());
    cellsSet.append(midH()   .values());
    cellsSet.append(bot()    .values());
    cellsSet.append(left()   .values());
    cellsSet.append(midV()   .values());
    cellsSet.append(right()  .values());
    cellsSet.append(diagInc().values());
    cellsSet.append(diagDec().values());

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

void BoardModel::clearPieces()
{
    for (int i = 0; i < NUM_CELLS; i++)
    {
        board_[i] = PIECE_TYPE_NONE;
    }
}

SimpleBoard BoardModel::simpleBoard()
{
    return SimpleBoard(board_);
}

void BoardModel::setSimpleBoard(SimpleBoard sBoard)
{
    board_ = sBoard.board;
}

bool BoardModel::gameOver()
{
    return winnerPiece() != PIECE_TYPE_NONE || !board_.contains(PIECE_TYPE_NONE);
}

void BoardModel::setPiece(Cell cell, PieceType piece)
{
    if (cell == CELL_NONE)
    {
        qDebug() << "Cannot set piece of CELL_NONE";
        Q_ASSERT(false);
        return;
    }

    board_[cell] = piece;
}

PieceType BoardModel::getPiece(Cell cell)
{
    if (cell == CELL_NONE)
    {
        qDebug() << "Cannot get piece from CELL_NONE";
        Q_ASSERT(false);
        return PIECE_TYPE_NONE;
    }

    return board_[(int) cell];
}

Cell BoardModel::availableWin(PieceType piece)
{
    QList<QMap<Cell, PieceType>> cellsSet;
    cellsSet.append(top());
    cellsSet.append(midH());
    cellsSet.append(bot());
    cellsSet.append(left());
    cellsSet.append(midV());
    cellsSet.append(right());
    cellsSet.append(diagInc());
    cellsSet.append(diagDec());

    foreach (auto cells, cellsSet)
    {
        if (containsTwoAndEmpty(cells.values(), piece))
        {
            foreach (Cell cell, cells.keys())
            {
                if (cells[cell] == PIECE_TYPE_NONE)
                {
                    return cell;
                }
            }
        }
    }

    return CELL_NONE;
}

QList<QMap<Cell, PieceType> > BoardModel::winLines()
{
    QList<QMap<Cell, PieceType>> cellsSet;
    cellsSet.append(top());
    cellsSet.append(midH());
    cellsSet.append(bot());
    cellsSet.append(left());
    cellsSet.append(midV());
    cellsSet.append(right());
    cellsSet.append(diagInc());
    cellsSet.append(diagDec());
    return cellsSet;
}

QList<Cell> BoardModel::cells()
{
    QList<Cell> cells;
    cells.append(CELL_TOP_LEFT );
    cells.append(CELL_TOP_MID  );
    cells.append(CELL_TOP_RIGHT);
    cells.append(CELL_MID_LEFT );
    cells.append(CELL_MID_MID  );
    cells.append(CELL_MID_RIGHT);
    cells.append(CELL_BOT_LEFT );
    cells.append(CELL_BOT_MID  );
    cells.append(CELL_BOT_RIGHT);
    return cells;
}

QList<Cell> BoardModel::emptyCells()
{
    QList<Cell> emptyCells;
    foreach (Cell cell, cells())
    {
        if (board_[cell] == PIECE_TYPE_NONE)
        {
            emptyCells.append(cell);
        }
    }
    return emptyCells;
}

QMap<Cell, PieceType> BoardModel::top()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_TOP_LEFT,  board_[CELL_TOP_LEFT]);
    top.insert(CELL_TOP_MID,   board_[CELL_TOP_MID]);
    top.insert(CELL_TOP_RIGHT, board_[CELL_TOP_RIGHT]);
    return top;
}

QMap<Cell, PieceType> BoardModel::midH()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_MID_LEFT,  board_[CELL_MID_LEFT]);
    top.insert(CELL_MID_MID ,  board_[CELL_MID_MID]);
    top.insert(CELL_MID_RIGHT, board_[CELL_MID_RIGHT]);
    return top;
}

QMap<Cell, PieceType> BoardModel::bot()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_BOT_LEFT , board_[CELL_BOT_LEFT ]);
    top.insert(CELL_BOT_MID  , board_[CELL_BOT_MID  ]);
    top.insert(CELL_BOT_RIGHT, board_[CELL_BOT_RIGHT]);
    return top;
}

QMap<Cell, PieceType> BoardModel::left()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_TOP_LEFT, board_[CELL_TOP_LEFT]);
    top.insert(CELL_MID_LEFT, board_[CELL_MID_LEFT]);
    top.insert(CELL_BOT_LEFT, board_[CELL_BOT_LEFT]);
    return top;
}

QMap<Cell, PieceType> BoardModel::midV()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_TOP_MID, board_[CELL_TOP_MID]);
    top.insert(CELL_MID_MID, board_[CELL_MID_MID]);
    top.insert(CELL_BOT_MID, board_[CELL_BOT_MID]);
    return top;
}

QMap<Cell, PieceType> BoardModel::right()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_TOP_RIGHT, board_[CELL_TOP_RIGHT]);
    top.insert(CELL_MID_RIGHT, board_[CELL_MID_RIGHT]);
    top.insert(CELL_BOT_RIGHT, board_[CELL_BOT_RIGHT]);
    return top;
}

QMap<Cell, PieceType> BoardModel::diagDec()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_TOP_LEFT , board_[CELL_TOP_LEFT ]);
    top.insert(CELL_MID_MID  , board_[CELL_MID_MID  ]);
    top.insert(CELL_BOT_RIGHT, board_[CELL_BOT_RIGHT]);
    return top;
}

QMap<Cell, PieceType> BoardModel::diagInc()
{
    QMap<Cell, PieceType> top;
    top.insert(CELL_TOP_RIGHT, board_[CELL_TOP_RIGHT]);
    top.insert(CELL_MID_MID  , board_[CELL_MID_MID]);
    top.insert(CELL_BOT_LEFT , board_[CELL_BOT_LEFT]);
    return top;
}

PieceType BoardModel::containsOnly(QList<PieceType> cells)
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

bool BoardModel::containsTwoAndEmpty(QList<PieceType> cells, PieceType piece)
{
    return cells.count(piece) == 2 && cells.count(PIECE_TYPE_NONE) == 1;
}


