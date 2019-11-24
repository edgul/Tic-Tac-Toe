#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include "data.h"

class Message
{
public:
    explicit Message(QString str);
    explicit Message(Target t, Function f, Quad q);
    explicit Message(Target t, Function f, QString board);

    Target getTarget();
    Function getFunction();
    Quad getQuad();
    QString getBoard();
    QString toString();

    void setMessage(QString rawStr);
    void setTFQ(Target t, Function f, Quad q);
    void setTFB(Target t, Function f, QString board);

private:
    Target target;
    Function function;
    Quad quad;
    QString board;

};

#endif // MESSAGE_H
