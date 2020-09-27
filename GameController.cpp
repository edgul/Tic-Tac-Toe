#include "GameController.h"

#include "data/Message.h"

GameController::GameController()
{
    connect(&tcpServer_, SIGNAL(receivedData(QString,int)), SLOT(onReceivedData(QString, int)));
    connect(&tcpServer_, SIGNAL(userDisconnected(int)), SLOT(onUserDisconnected(int)));

}

void GameController::onReceivedData(QString data, int user)
{
    messageStreams_[user] += data;

    int firstDelimiter;
    while ((firstDelimiter = messageStreams_[user].indexOf(DELIMITER)) != -1)
    {
        QString messageStr = messageStreams_[user].mid(0, firstDelimiter);
        messageStreams_[user] = messageStreams_[user].remove(0, firstDelimiter+4);
        handleMessage(Message::messageFromString(messageStr), user);
    }
}

void GameController::onGameInit(Player p1, Player p2)
{
    tcpServer_.sendMessage(Message::gameInitMessage(p1.getPieceType()), p1.getUser());
    tcpServer_.sendMessage(Message::gameInitMessage(p2.getPieceType()), p2.getUser());
}

void GameController::onGameStateUpdated(Player p1 , Player p2, BoardModel board)
{
    Message msg = Message::gameUpdateMessage(board.simpleBoard());
    tcpServer_.sendMessage(msg, p1.getUser());
    tcpServer_.sendMessage(msg, p2.getUser());
}

void GameController::onGameEnded(Player winningPlayer)
{
    qDebug() << "GAME ENDED: " << winningPlayer.getPieceType();

    Game *game = static_cast<Game*>(sender());
    Message msg = Message::gameEndMessage(winningPlayer.getPieceType());
    Player p1 = game->getPlayerX();
    Player p2 = game->getPlayerO();

    tcpServer_.sendMessage(msg, p1.getUser());
    tcpServer_.sendMessage(msg, p2.getUser());

    players_.removeOne(p1);
    players_.removeOne(p2);

    games_.removeOne(game);
    game->deleteLater();
}

void GameController::onUserDisconnected(int user)
{
    Player player = getPlayerByUser(user);
    players_.removeOne(player);

    Game *game = gameWithUser(user);

    if (game)
    {
        if (game->getActive())
        {
            if (game->getPlayerX() == player || game->getPlayerO() == player)
            {
                // qDebug() << "Piece type quit: " << player.getPieceType();
                game->quit(player.getPieceType());
            }
        }
    }
    else
    {
        qDebug() << "Game already removed";
    }
}

Game *GameController::gameWithUser(int user)
{
    foreach (Game *game, games_)
    {
        if (game->getPlayerO().getUser() == user)
        {
            return game;
        }
        else if (game->getPlayerX().getUser() == user)
        {
            return game;
        }
    }

    return nullptr;
}

int GameController::indexOfFirstPlayerNotInGame()
{
    for (int i = 0; i < players_.length(); i++)
    {
        if (players_[i].getPieceType() == PIECE_TYPE_NONE)
        {
            return i;
        }
    }

    return -1;
}

Player GameController::getPlayerByUser(int user)
{
    foreach (Player p, players_)
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
            players_[index] = Player(players_[index].getUser(), PIECE_TYPE_X);
            Player newPlayer(user, PIECE_TYPE_O);
            players_.append(newPlayer);

            Game *game = new Game();
            connect(game, SIGNAL(gameInit(Player,Player)), SLOT(onGameInit(Player,Player)));
            connect(game, SIGNAL(gameStateUpdated(Player, Player, BoardModel)), SLOT(onGameStateUpdated(Player, Player, BoardModel)));
            connect(game, SIGNAL(gameEnded(Player)), SLOT(onGameEnded(Player)));
            games_.append(game);

            game->start(players_[index], newPlayer);
        }
        else
        {
            Player newPlayer(user, PIECE_TYPE_NONE);
            players_.append(newPlayer);
        }
    }
    else if (msg.getFunction() == FUNCTION_GAME_QUIT)
    {
        Player quitting = getPlayerByUser(user);

        Game *game = gameWithUser(user);

        if (game)
        {
            game->quit(quitting.getPieceType());
        }
        else
        {
            qDebug() << "Couldn't find game of quitting user";
        }
    }
    else if (msg.getFunction() == FUNCTION_GAME_PLACE)
    {
        Player actingPlayer =  getPlayerByUser(user);

        Game *game = gameWithUser(user);

        if (game)
        {
            if (game->getActive() && actingPlayer.getPieceType() == game->currentTurnPiece())
            {
                game->placePiece(msg.getCell());
                game->checkForGameOver();
            }
        }
        else
        {
            qDebug() << "Couldn't find game belonging to user (placing piece): " << user;
        }
    }
}

