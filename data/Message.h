#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include "data.h"

#define DELIMITER " TTT "

class Message
{
public:
    explicit Message(QString str);
    explicit Message(Target t, Function f);
    explicit Message(Target t, Function f, Cell c);
    explicit Message(Target t, Function f, SimpleBoard board);
    explicit Message(Target t, Function f, PieceType p);

    Target getTarget();
    Function getFunction();
    Cell getCell();
    PieceType getPieceType();
    QString toString();
    SimpleBoard getSimpleBoard();

    void setMessage(QString rawStr);
    void setTFC(Target t, Function f, Cell c);
    void setTFB(Target t, Function f, SimpleBoard board);
    void setTFP(Target t, Function f, PieceType p);

private:
    Target target;
    Function function;
    Cell cell;
    QString board;
    SimpleBoard sBoard;
    PieceType pieceType;

};

#endif // MESSAGE_H
