#include "GameController.h"

#include "data/Message.h"

GameController::GameController() :
    messageStream("")
{
    connect(&tcpServer, SIGNAL(receivedData(QString,int)), SLOT(onReceivedData(QString, int)));
    connect(&tcpServer, SIGNAL(userDisconnected(int)), SLOT(onUserDisconnected(int)));

    connect(&game, SIGNAL(gameInit(Player,Player)), SLOT(onGameInit(Player,Player)));
    connect(&game, SIGNAL(gameStateUpdated(Player, Player, BoardModel)), SLOT(onGameStateUpdated(Player, Player, BoardModel)));
    connect(&game, SIGNAL(gameEnded(Player)), SLOT(onGameEnded(Player)));
}

void GameController::onReceivedData(QString data, int user)
{
    messageStream += data;

    int firstDelimiter;
    while ((firstDelimiter = messageStream.indexOf(DELIMITER)) != -1)
    {
        QString messageStr = messageStream.mid(0, firstDelimiter);
        messageStream = messageStream.remove(0, firstDelimiter+4);
        handleMessage(Message::messageFromString(messageStr), user);
    }
}

void GameController::onGameInit(Player p1, Player p2)
{
    tcpServer.sendMessage(Message::gameInitMessage(p1.getPieceType()), p1.getUser());
    tcpServer.sendMessage(Message::gameInitMessage(p2.getPieceType()), p2.getUser());
}

void GameController::onGameStateUpdated(Player p1 , Player p2, BoardModel board)
{
    Message msg = Message::gameUpdateMessage(board.simpleBoard());
    tcpServer.sendMessage(msg, p1.getUser());
    tcpServer.sendMessage(msg, p2.getUser());
}

void GameController::onGameEnded(Player winningPlayer)
{
    qDebug() << "GAME ENDED: " << winningPlayer.getPieceType();

    Message msg = Message::gameEndMessage(winningPlayer.getPieceType());
    Player p1 = game.getPlayerX();
    Player p2 = game.getPlayerO();

    tcpServer.sendMessage(msg, p1.getUser());
    tcpServer.sendMessage(msg, p2.getUser());

    players.removeOne(p1);
    players.removeOne(p2);
}

void GameController::onUserDisconnected(int user)
{
    Player player = getPlayerByUser(user);
    players.removeOne(player);

    if (game.getActive())
    {
        if (game.getPlayerX() == player || game.getPlayerO() == player)
        {
            // qDebug() << "Piece type quit: " << player.getPieceType();
            game.quit(player.getPieceType());
        }
    }
}

int GameController::indexOfFirstPlayerNotInGame()
{
    for (int i = 0; i < players.length(); i++)
    {
        if (players[i].getPieceType() == PIECE_TYPE_NONE)
        {
            return i;
        }
    }

    return -1;
}

Player GameController::getPlayerByUser(int user)
{
    foreach (Player p, players)
    {
        if (p.getUser() == user)
        {
            return p;
        }
    }

    return Player();
}

void GameController::handleMessage(Message msg, int user)
{
    if (msg.getFunction() == FUNCTION_GAME_START)
    {
        int index = indexOfFirstPlayerNotInGame();

        if (index != -1)
        {
            players[index] = Player(players[index].getUser(), PIECE_TYPE_X);
            Player newPlayer(user, PIECE_TYPE_O);
            players.append(newPlayer);

            game.start(players[index], newPlayer);
        }
        else
        {
            Player newPlayer(user, PIECE_TYPE_NONE);
            players.append(newPlayer);
        }
    }
    else if (msg.getFunction() == FUNCTION_GAME_QUIT)
    {
        Player quitting = getPlayerByUser(user);
        game.quit(quitting.getPieceType());
    }
    else if (msg.getFunction() == FUNCTION_GAME_PLACE)
    {
        Player actingPlayer =  getPlayerByUser(user);

        if (game.getActive() && actingPlayer.getPieceType() == game.currentTurnPiece())
        {
            game.placePiece(msg.getCell());
            game.checkForGameOver();
        }
    }
}

