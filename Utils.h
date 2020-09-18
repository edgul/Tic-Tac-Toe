#ifndef UTILS_H
#define UTILS_H

#include "data/data.h"

namespace Utils
{
    PieceType opponentPiece(PieceType piece);

    QString pieceToStr(PieceType piece);
    PieceType strToPiece(QString str);
    QString simpleBoardToStr(SimpleBoard board);
    SimpleBoard strToSimpleBoard(QString str);
}

#endif // UTILS_H
