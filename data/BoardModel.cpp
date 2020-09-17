#include "data/BoardModel.h"

#include <QDebug>

BoardModel::BoardModel()
{
    define_winning_sets();

    // init empty board
    for (int i = 0; i < 9; i++)
    {
        board.append(EMPTY_CELL);
    }
}

BoardModel::BoardModel(SimpleBoard sBoard) :
    board_(sBoard.board)
{

}

void BoardModel::clear()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = EMPTY_CELL;
    }
}

bool BoardModel::full()
{
    bool full = true;

    foreach (QString s, board)
    {
        if (s == EMPTY_CELL)
        {
            full = false;
            break;
        }
    }

    return full;
}

void BoardModel::place(QString piece, Quad q)
{
    int q_int = (int) q;
    board[q_int] = piece;

}

bool BoardModel::quad_empty(Quad quad)
{
    bool empty = false;

    if (board[quad] == EMPTY_CELL) empty = true;

    return empty;
}

QString BoardModel::winner()
{
    QString winner = "";

    foreach (QList<Quad> win, wins)
    {
        bool these_quads_win = true;

        foreach(Quad quad, win)
        {
            if (!quads_with_piece(PLAYER_X).contains(quad))
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
            if (!quads_with_piece(PLAYER_O).contains(quad))
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

int BoardModel::pieces()
{
    int p = 0;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] != EMPTY_CELL)
        {
            p++;
        }
    }

    return p;
}

int BoardModel::size()
{
    return board.length();
}

QString BoardModel::piece_at(int index)
{
    return board[index];
}

int BoardModel::productivity(Quad move, QString piece_type)
{
    int p = 0;

    QString other_piece = PLAYER_X;
    if (piece_type == PLAYER_X) other_piece = PLAYER_O;

    foreach (QList<Quad> win_line, wins)
    {
        if (win_line.contains(move))
        {
            bool has_other_piece = false;
            foreach (Quad i , win_line)
            {
                if (board[i] == other_piece)
                {
                    has_other_piece = true;
                    break;
                }
            }

            if (!has_other_piece)
            {

                p++;
            }
        }
    }

    return p;
}

QList<Quad> BoardModel::quads_with_piece(QString piece)
{
    QList<Quad> quads;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] == piece)
        {
            quads.append( (Quad) i);
        }
    }

    return quads;
}

Quad BoardModel::available_win(QString piece_type)
{
    Quad win_quad = QUAD_NONE;

    QList<Quad> empty_quads = quads_with_piece(EMPTY_CELL);

    foreach (Quad quad, empty_quads)
    {
        foreach (QList<Quad> win_line, wins)
        {
            int count = 0;
            if (win_line.contains(quad))
            {
                foreach( Quad q, win_line)
                {
                    if (board[q] == piece_type)
                    {
                        count ++;
                    }
                }
            }

            if (count == 2)
            {
                win_quad = quad;
                break;
            }
        }
    }

    return win_quad;
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

void BoardModel::define_winning_sets()
{
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


