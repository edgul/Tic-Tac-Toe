#include "Message.h"

#include <QList>

Message::Message(QString str)
{
    setMessage(str);
}

Message::Message(Target t, Function f, Quad q)
{
    setTFQ(t,f,q);
}

Message::Message(Target t, Function f, QString board)
{
    setTFB(t,f,board);
}

Target Message::getTarget()
{
    return target;
}

Function Message::getFunction()
{
    return function;
}

Quad Message::getQuad()
{
    return quad;
}

QString Message::getBoard()
{
    return board;
}

void Message::setMessage(QString rawStr)
{
    QString trimmedStr = rawStr.trimmed();

    QList<QString> tokens = trimmedStr.split(" ");

    if (tokens.count() > 0)
    {
        target = static_cast<Target>(tokens[0].toInt());
    }
    else if (tokens.count() > 1)
    {
        function = static_cast<Function>(tokens[1].toInt());
    }
    else if (tokens.count() > 2)
    {
        QString something = tokens[2];

        if (something.length() == 1)
        {
            quad = static_cast<Quad>(tokens[2].toInt());
        }
        else
        {
            board = tokens[2];
        }
    }
}

void Message::setTFQ(Target t, Function f, Quad q)
{

}

void Message::setTFB(Target t, Function f, QString board)
{
    target = t;
    function = f;
    quad = QUAD_NONE;
    this->board = board;
}

QString Message::toString()
{
    QString result;
    result += QString::number(static_cast<int>(target)) + " ";
    result += QString::number(static_cast<int>(function)) + " ";

    if (quad != QUAD_NONE)
    {
        result += QString::number(static_cast<int>(quad));
    }
    else
    {
        result += board;
    }

    return result;
}
