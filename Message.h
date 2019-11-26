#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include "data.h"

class Message
{
public:
    explicit Message(QString str);
    explicit Message(Target t, Function f);
    explicit Message(Target t, Function f, Quad q);
    explicit Message(Target t, Function f, QString board);
    explicit Message(Target t, Function f, PieceType p);

    Target getTarget();
    Function getFunction();
    Quad getQuad();
    QString getBoardStr();
    PieceType getPieceType();
    QString toString();

    void setMessage(QString rawStr);
    void setTFQ(Target t, Function f, Quad q);
    void setTFB(Target t, Function f, QString board);
    void setTFP(Target t, Function f, PieceType p);

private:
    Target target;
    Function function;
    Quad quad;
    QString board;
    PieceType pieceType;

};

#endif // MESSAGE_H
