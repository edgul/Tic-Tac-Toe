#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include "data.h"


class BoardModel
{
public:
    BoardModel();
    BoardModel(SimpleBoard sBoard);

    // New
    PieceType winnerPiece();
    void clearPieces();
    SimpleBoard simpleBoard();
    void setSimpleBoard(SimpleBoard sBoard);
    bool gameOver();
    void setPiece(Cell cell, PieceType piece);
    PieceType getPiece(Cell cell);
    Cell availableWin(PieceType piece);
    QList<QMap<Cell, PieceType>> winLines();
    QList<Cell> cells();
    QList<Cell> emptyCells();

    // OLD
    // modifiers
    void set_board_from_string(QString b_string);

    QString toString();

private:
    QList<QString> board;

    QList<PieceType> board_ = { PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                                PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                                PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE
                              };

    QMap<Cell, PieceType> top();
    QMap<Cell, PieceType> midH();
    QMap<Cell, PieceType> bot();
    QMap<Cell, PieceType> left();
    QMap<Cell, PieceType> midV();
    QMap<Cell, PieceType> right();
    QMap<Cell, PieceType> diagDec();
    QMap<Cell, PieceType> diagInc();

    PieceType containsOnly(QList<PieceType> cells);
    bool containsTwoAndEmpty(QList<PieceType> cells, PieceType piece);

};

#endif // BOARD_H
