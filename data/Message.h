#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include "data.h"

#define DELIMITER " TTT "

class Message
{
public:
    static Message messageFromString(QString str);

    // server sends
    static Message gameInitMessage(PieceType piece);
    static Message gameUpdateMessage(SimpleBoard board);
    static Message gameEndMessage(PieceType winnerPiece);

    // client sends
    static Message gamePlacePiece(Cell cell);
    static Message gameStart();

    Function getFunction();
    Cell getCell();
    PieceType getPieceType();
    SimpleBoard getSimpleBoard();
    QString toString();

private:
    Function function = FUNCTION_NONE;
    Cell cell = CELL_NONE;
    SimpleBoard sBoard;
    PieceType pieceType = PIECE_TYPE_NONE;

    explicit Message();
    void setFunction(Function f);
    void setCell(Cell c);
    void setPieceType(PieceType p);
    void setSimpleBoard(SimpleBoard sb);
    void setMessage(QString rawStr);
};

#endif // MESSAGE_H
