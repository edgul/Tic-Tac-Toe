#include "Message.h"

#include <QList>
#include <QDebug>
#include <Utils.h>

const int FUNCTION_INDEX = 0;
const int GAME_END_WINNER_INDEX = 1;
const int GAME_INIT_PLAYER_PIECE_INDEX = 1;
const int GAME_PLACE_CELL = 1;
const int GAME_UPDATE_BOARD_STR = 1;

/*
client:
*******
GAME_START
GAME_PLACE Cell
GAME_QUIT PieceType

server:
*******
GAME_INIT PieceType
GAME_UPDATE Board
GAME_END PieceType
*/
Message::Message()
{
    function = FUNCTION_NONE;
    cell = CELL_NONE;
    sBoard = SimpleBoard();
    pieceType = PIECE_TYPE_NONE;
}

Message Message::messageFromString(QString str)
{
    Message msg;
    msg.setMessage(str);
    return msg;
}

Message Message::gameInitMessage(PieceType piece)
{
    Message msg;
    msg.setFunction(FUNCTION_GAME_INIT);
    msg.setPieceType(piece);
    return msg;
}

Message Message::gameUpdateMessage(SimpleBoard board)
{
    Message msg;
    msg.setFunction(FUNCTION_GAME_UPDATE);
    msg.setSimpleBoard(board);
    return msg;
}

Message Message::gameEndMessage(PieceType winnerPiece)
{
    Message msg;
    msg.setFunction(FUNCTION_GAME_END);
    msg.setPieceType(winnerPiece);
    return msg;
}

Message Message::gamePlacePiece(Cell cell)
{
    Message msg;
    msg.setFunction(FUNCTION_GAME_PLACE);
    msg.setCell(cell);
    return msg;
}

Message Message::gameStart()
{
    Message msg;
    msg.setFunction(FUNCTION_GAME_START);
    return msg;
}

Function Message::getFunction()
{
    return function;
}

void Message::setFunction(Function f)
{
    function = f;
}

Cell Message::getCell()
{
    return cell;
}

void Message::setCell(Cell c)
{
    cell = c;
}

PieceType Message::getPieceType()
{
    return pieceType;
}

void Message::setPieceType(PieceType p)
{
    pieceType = p;
}

SimpleBoard Message::getSimpleBoard()
{
    return sBoard;
}

void Message::setSimpleBoard(SimpleBoard sb)
{
    sBoard = sb;
}

void Message::setMessage(QString rawStr)
{
    QString trimmedStr = rawStr.trimmed();

    QList<QString> tokens = trimmedStr.split(" ");

    if (tokens.count() > 0)
    {
        function = static_cast<Function>(tokens[FUNCTION_INDEX].toInt());
    }

    if (tokens.count() > 1)
    {
        if (function == FUNCTION_GAME_END)
        {
            pieceType = static_cast<PieceType>(tokens[GAME_END_WINNER_INDEX].toInt());
        }
        else if (function == FUNCTION_GAME_INIT)
        {
            pieceType = static_cast<PieceType>(tokens[GAME_INIT_PLAYER_PIECE_INDEX].toInt());
        }
        else if (function == FUNCTION_GAME_PLACE)
        {
            cell = static_cast<Cell>(tokens[GAME_PLACE_CELL].toInt());
        }
        else if (function == FUNCTION_GAME_UPDATE)
        {
            sBoard = Utils::strToSimpleBoard(tokens[GAME_UPDATE_BOARD_STR]);
        }
        else
        {
            qDebug() << "Failure to parse message string properly";
            Q_ASSERT(false);
        }
    }
}

QString Message::toString()
{
    QString result;
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
