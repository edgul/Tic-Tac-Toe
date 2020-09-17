#include "Message.h"

#include <QList>

#include <QDebug>

Message::Message(QString str)
{
    setMessage(str);
}

Message::Message(Target t, Function f)
{
    target = t;
    function = f;
    quad = QUAD_NONE;
    board = "";
    pieceType = PIECE_TYPE_NONE;
}

Message::Message(Target t, Function f, Quad q)
{
    setTFQ(t,f,q);
}

Message::Message(Target t, Function f, QString board)
{
    setTFB(t,f,board);
}

Message::Message(Target t, Function f, PieceType p)
{
    setTFP(t,f,p);
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

QString Message::getBoardStr()
{
    return board;
}

PieceType Message::getPieceType()
{
    return pieceType;
}

void Message::setMessage(QString rawStr)
{
    QString trimmedStr = rawStr.trimmed();

    QList<QString> tokens = trimmedStr.split(" ");

    if (tokens.count() > 0)
    {
        target = static_cast<Target>(tokens[0].toInt());
    }

    if (tokens.count() > 1)
    {
        function = static_cast<Function>(tokens[1].toInt());
    }

    if (tokens.count() > 2)
    {
        if (function == FUNCTION_GAME_END)
        {
            pieceType = static_cast<PieceType>(tokens[2].toInt());
        }
        else if (function == FUNCTION_GAME_INIT)
        {
            pieceType = static_cast<PieceType>(tokens[2].toInt());
        }
        else if (function == FUNCTION_GAME_PLACE)
        {
            quad = static_cast<Quad>(tokens[2].toInt());
        }
        else if (function == FUNCTION_GAME_UPDATE)
        {
            board = tokens[2];
        }
        else
        {
            qDebug() << "Failure to parse message string properly";
            Q_ASSERT(false);
        }
    }
}

void Message::setTFQ(Target t, Function f, Quad q)
{
    target = t;
    function = f;
    quad = q;
    board = "";
    pieceType = PIECE_TYPE_NONE;
}

void Message::setTFB(Target t, Function f, QString board)
{
    target = t;
    function = f;
    quad = QUAD_NONE;
    this->board = board;
    pieceType = PIECE_TYPE_NONE;
}

void Message::setTFP(Target t, Function f, PieceType p)
{
    target = t;
    function = f;
    pieceType = p;
    quad = QUAD_NONE;
    board = "";
}

QString Message::toString()
{
    QString result;
    result += QString::number(static_cast<int>(target)) + " ";
    result += QString::number(static_cast<int>(function)) + " ";

    if (function == FUNCTION_GAME_PLACE)
    {
        result += QString::number(static_cast<int>(quad));
    }
    else if (function == FUNCTION_GAME_UPDATE)
    {
        result += board;
    }
    else if (function == FUNCTION_GAME_END)
    {
        result += QString::number(static_cast<int>(pieceType));
    }
    else if (function == FUNCTION_GAME_INIT)
    {
        result += QString::number(static_cast<int>(pieceType));
    }

    return result;
}
