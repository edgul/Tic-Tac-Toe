#include "GameController.h"

#include "Message.h"

GameController::GameController() :
    messageStream("")
{
    connect(&tcp_server, SIGNAL(receivedData(QString,int)), SLOT(onReceivedData(QString, int)));
    connect(&tcp_server, SIGNAL(userDisconnected(int)), SLOT(onUserDisconnected(int)));

    connect(&game, SIGNAL(gameInit(Player,Player)), SLOT(onGameInit(Player,Player)));
    connect(&game, SIGNAL(gameStateUpdated(Player, Player, Board)), SLOT(onGameStateUpdated(Player, Player, Board)));
    connect(&game, SIGNAL(gameEnded(Player)), SLOT(onGameEnded(Player)));
}

void GameController::onReceivedData(QString data, int user)
{
    messageStream += data;

    int firstDelimiter;
    while ((firstDelimiter = messageStream.indexOf(DELIMITER)) != -1)
    {
        QString message = messageStream.mid(0, firstDelimiter);
        messageStream = messageStream.remove(0, firstDelimiter+4);
        processMessage(message, user);
    }
}

void GameController::onGameInit(Player p1, Player p2)
{
    Message msg(TARGET_GAME, FUNCTION_GAME_INIT, p1.getPieceType());
    tcp_server.sendMessage(msg, p1.getUser());
    tcp_server.sendMessage(msg, p2.getUser());
}

void GameController::onGameStateUpdated(Player p1 , Player p2, Board board)
{
    Message msg(TARGET_GAME, FUNCTION_GAME_UPDATE, board.toString());
    tcp_server.sendMessage(msg, p1.getUser());
    tcp_server.sendMessage(msg, p2.getUser());
}

void GameController::onGameEnded(Player winningPlayer)
{
    Message msg(TARGET_GAME, FUNCTION_GAME_END, winningPlayer.getPieceType());

    Player p1 = game.getPlayer1();
    Player p2 = game.getPlayer2();

    tcp_server.sendMessage(msg, p1.getUser());
    tcp_server.sendMessage(msg, p2.getUser());
}

void GameController::onUserDisconnected(int user)
{
    Player player(user);
    players.removeOne(player);

    if (game.getActive())
    {
        if (game.getPlayer1() == player || game.getPlayer2() == player)
        {
            game.quit(player);
        }
    }
}

void GameController::processMessage(QString messageStr, int user)
{
    Message msg(messageStr);

    if (msg.getTarget() == TARGET_NONE)
    {
        qDebug() << "Received Target NONE...";
    }
    else if (msg.getTarget() == TARGET_GAME)
    {
        handleGameMessage(msg, user);
    }
    else
    {
        Q_ASSERT(false);
    }
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
            if (player.getPieceType() == PIECE_TYPE_NONE)
            {
                otherPlayer = &player;
            }
        }

        // Add player to list
        PieceType newPieceType = PIECE_TYPE_NONE;
        if (otherPlayer)
        {
            otherPlayer->setPlayerType(PIECE_TYPE_X);
            newPieceType = PIECE_TYPE_O;

            Player newPlayer(user, newPieceType);
            players.append(newPlayer);
            game.startMultiplayer(*otherPlayer, newPlayer);
        }
        else
        {
            Player newPlayer(user, newPieceType);
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
        game.checkForGameOver();

    }
}

