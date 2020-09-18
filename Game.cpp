#include "Game.h"

#define MSG_TURN_X "X's turn"
#define MSG_TURN_O "O's turn"
#define MSG_WIN_X  "X wins!"
#define MSG_WIN_O  "O wins!"
#define MSG_TIE    "Tie game."

#include <QDebug>

Game::Game()
{
    turn_x = true;
    active_ = false;
    singlePlayer = true;
}

void Game::init()
{
    board.clearPieces();
    turn_x = true;

    QString msg = MSG_TURN_X;
    emit update_msg_label(msg);
    active_ = true;
}

void Game::startMultiplayer(Player p1, Player p2)
{
    if (p1.getPieceType() == PIECE_TYPE_X)
    {
        playerX = p1;
        playerO = p2;
    }
    else
    {
        playerX = p2;
        playerO = p1;
    }

    init();
    singlePlayer = false;
    emit gameInit(playerX, playerO);
}

bool Game::getActive()
{
    return active_;
}

void Game::checkForGameOver()
{
    bool game_over = false;

    // check for game over
    Player winner;
    if (board.winnerPiece() == PIECE_TYPE_X) // x wins
    {
        QString msg = MSG_WIN_X;
        emit update_msg_label(msg);

        winner = playerX;
        winner.setPlayerType(PIECE_TYPE_X); // hack because value lost FSR

        game_over = true;

    }
    else if (board.winnerPiece() == PIECE_TYPE_O) // o wins
    {
        QString msg = MSG_WIN_O;
        emit update_msg_label(msg);
        winner = playerO;
        winner.setPlayerType(PIECE_TYPE_O); // hack because value lost FSR

        game_over = true;
    }
    else if (board.emptyCells().length() == 0) // tie
    {
        QString msg = MSG_TIE;
        emit update_msg_label(msg);

        game_over = true;
    }

    if (game_over)
    {
        // stop taking user input when the game is over
        active_ = false;
        emit gameEnded(winner);
    }
    else
    {
        turn_x = !turn_x;

        // update label
        QString msg = MSG_TURN_X;
        if (!turn_x) msg = MSG_TURN_O;
        emit update_msg_label(msg); 
    }
}

void Game::placePiece(Player player, Cell cell)
{
    if (active_) // accepting input from user
    {
        // TODO: simplify logic
        bool proceed = false;

        if (player.getPieceType() == PIECE_TYPE_X)
        {
            if (turn_x) proceed = true;
        }
        else
        {
            if (!turn_x) proceed = true;
        }

        if (proceed)
        {
            if (board.getPiece(cell) == PIECE_TYPE_NONE) // valid move
            {
                // Place piece
                board.setPiece(cell, getTurnPiece());
                emit gameStateUpdated(playerX, playerO, board);
            }
        }
    }
}

void Game::quit(Player quittingPlayer)
{
    Player winningPlayer;
    if (quittingPlayer == playerX)
    {
        winningPlayer = playerO;
    }
    else
    {
        winningPlayer = playerX;
    }

    emit gameEnded(winningPlayer);
}

Player Game::getPlayer1()
{
    return playerX;
}

Player Game::getPlayer2()
{
    return playerO;
}

Player Game::currentTurnPlayer()
{
    if (turn_x)
    {
        return playerX;
    }
    else
    {
        return playerO;
    }
}

PieceType Game::getTurnPiece()
{
    PieceType turn_piece = PIECE_TYPE_NONE;
    if (turn_x)
    {
        turn_piece = PIECE_TYPE_X;
    }
    else
    {
        turn_piece = PIECE_TYPE_O;
    }

    return turn_piece;
}

