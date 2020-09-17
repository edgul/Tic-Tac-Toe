#include "Utils.h"

namespace Utils
{

PieceType opponentPiece(PieceType piece)
{
    if (piece == PIECE_TYPE_X) return PIECE_TYPE_O;
    if (piece == PIECE_TYPE_O) return PIECE_TYPE_X;
    return PIECE_TYPE_NONE;
}

}
