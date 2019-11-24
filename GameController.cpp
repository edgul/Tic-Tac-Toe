#include "GameController.h"

#include "Message.h"

GameController::GameController() :
    messageStream("")
{
    connect(&tcp_server, SIGNAL(received_data(QString)), SLOT(onReceivedData(QString, int)));
    connect(&game, SIGNAL(gameEnded(EndType,Player)), SLOT(onGameEnded(EndType,Player)));
}

void GameController::onReceivedData(QString data, int user)
{
    messageStream += data;

    int firstDelimiter;
    while ((firstDelimiter = messageStream.indexOf(DELIMITER)) != -1)
    {
        QString message = messageStream.mid(0, firstDelimiter-1);
        messageStream = messageStream.remove(0, firstDelimiter+2);
        qDebug() << "Received : " << message;

        processMessage(message, user);
    }
}

void GameController::onGameEnded(EndType endType, Player winningPlayer)
{
    // TODO:

    // send game ended
    // tcp_server.
}

void GameController::processMessage(QString messageStr, int user)
{
    Message msg(messageStr);

    if (msg.getTarget() == TARGET_NONE)
    {
        qDebug() << "Received Target NONE...";
    }
    else if (msg.getTarget() == TARGET_CONNECTION)
    {
        qDebug() << "Received Target CONNECTION";
        handleConnectionMessage(msg);
    }
    else
    {
        qDebug() << "Received Target GAME";
        handleGameMessage(msg, user);
    }
}

void GameController::handleConnectionMessage(Message msg)
{
    // TODO: control TcpServer connect/disconnect from here

    // if user disconnected while game in progress then inititate game quitting functions
}

void GameController::handleGameMessage(Message msg, int user)
{
    if (msg.getFunction() == FUNCTION_GAME_START)
    {
        // look for another to play with
        Player* otherPlayer = nullptr;
        for (int i = 0; i < players.length(); i++)
        {
            Player &player = players[i];
            if (player.getPlayerType() == PLAYER_TYPE_NONE)
            {
                otherPlayer = &player;
            }
        }

        PlayerType newPlayerType = PLAYER_TYPE_NONE;
        if (otherPlayer)
        {
            otherPlayer->setPlayerType(PLAYER_TYPE_X);
            newPlayerType = PLAYER_TYPE_O;

            Player newPlayer(user, newPlayerType);
            players.append(newPlayer);

            game.startMultiplayer(*otherPlayer, newPlayer);
        }
        else
        {
            Player newPlayer(user, newPlayerType);
            players.append(newPlayer);
        }

    }
    else if (msg.getFunction() == FUNCTION_GAME_QUIT)
    {
        Player quitting = players[players.indexOf(Player(user))];
        game.quit(quitting);
    }
    else if (msg.getFunction() == FUNCTION_GAME_PLACE)
    {
        Player actingPlayer = players[players.indexOf(Player(user))];
        game.placePiece(actingPlayer, msg.getQuad());
    }
}

