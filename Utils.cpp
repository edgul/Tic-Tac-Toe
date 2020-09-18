#include "Utils.h"

#include <QDebug>
#include "data/data.h"

namespace Utils
{

PieceType opponentPiece(PieceType piece)
{
    if (piece == PIECE_TYPE_X) return PIECE_TYPE_O;
    if (piece == PIECE_TYPE_O) return PIECE_TYPE_X;
    return PIECE_TYPE_NONE;
}

QString pieceToStr(PieceType piece)
{
    if (piece == PIECE_TYPE_X)    return PIECE_STR_X;
    if (piece == PIECE_TYPE_O)    return PIECE_STR_O;
    return PIECE_STR_NONE;
}

PieceType strToPiece(QString str)
{
    if (str == PIECE_STR_X)    return PIECE_TYPE_X;
    if (str == PIECE_STR_O)    return PIECE_TYPE_O;
    return PIECE_TYPE_NONE;
}

QString simpleBoardToStr(SimpleBoard board)
{
    QString str;
    foreach (PieceType piece, board.board)
    {
        str.append(pieceToStr(piece));
    }
    return str;
}

SimpleBoard strToSimpleBoard(QString str)
{
    if (str.length() != NUM_CELLS)
    {
        qDebug() << "Err: Can't convert string to simple board - incorrect char num";
        return SimpleBoard();
    }

    QList<PieceType> board;
    for (int i = 0; i < str.length(); i++)
    {
        board.append(strToPiece((QString)str[i]));
    }
    return board;
}



}
