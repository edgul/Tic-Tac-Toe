#include "Message.h"

#include <QList>
#include <QDebug>
#include <Utils.h>

Message::Message(QString str)
{
    setMessage(str);
}

Message::Message(Target t, Function f)
{
    target = t;
    function = f;
    cell = CELL_NONE;
    sBoard = SimpleBoard();
    pieceType = PIECE_TYPE_NONE;
}

Message::Message(Target t, Function f, Cell c)
{
    setTFC(t,f,c);
}

Message::Message(Target t, Function f, SimpleBoard board)
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

Cell Message::getCell()
{
    return cell;
}

PieceType Message::getPieceType()
{
    return pieceType;
}

SimpleBoard Message::getSimpleBoard()
{
    return sBoard;
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
            cell = static_cast<Cell>(tokens[2].toInt());
        }
        else if (function == FUNCTION_GAME_UPDATE)
        {
            sBoard = Utils::strToSimpleBoard(tokens[2]);
        }
        else
        {
            qDebug() << "Failure to parse message string properly";
            Q_ASSERT(false);
        }
    }
}

void Message::setTFC(Target t, Function f, Cell c)
{
    target = t;
    function = f;
    cell = c;
    sBoard = SimpleBoard();
    pieceType = PIECE_TYPE_NONE;
}

void Message::setTFB(Target t, Function f, SimpleBoard board)
{
    target = t;
    function = f;
    cell = CELL_NONE;
    sBoard = board;
    pieceType = PIECE_TYPE_NONE;
}

void Message::setTFP(Target t, Function f, PieceType p)
{
    target = t;
    function = f;
    pieceType = p;
    cell = CELL_NONE;
    sBoard = SimpleBoard();
}

QString Message::toString()
{
    QString result;
    result += QString::number(static_cast<int>(target)) + " ";
    result += QString::number(static_cast<int>(function)) + " ";

    if (function == FUNCTION_GAME_PLACE)
    {
        result += QString::number(static_cast<int>(cell));
    }
    else if (function == FUNCTION_GAME_UPDATE)
    {
        result += Utils::simpleBoardToStr(sBoard);
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
