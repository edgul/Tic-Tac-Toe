#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include "data.h"

#define EMPTY_CELL "-"

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
    void clear();
    void place(QString piece, Quad q);
    void set_board_from_string(QString b_string);

    QString winner();
    // accessors
    bool full();
    bool quad_empty(Quad quad);
    int pieces();
    int size();
    QString piece_at(int index);
    QList<Quad> quads_with_piece(QString piece);

    int productivity(Quad move, QString piece_type); // number of possible wins from this quad placement
    QList<QList<Quad>> wins;
    Quad available_win(QString piece_type);

    QString toString();

private:
    QList<QString> board;

    QList<PieceType> board_ = { PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                                PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE,
                                PIECE_TYPE_NONE, PIECE_TYPE_NONE, PIECE_TYPE_NONE
                              };

    void define_winning_sets();

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
