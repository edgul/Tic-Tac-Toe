#include "Game.h"

#define MSG_TURN_X "X's turn"
#define MSG_TURN_O "O's turn"
#define MSG_WIN_X  "X wins!"
#define MSG_WIN_O  "O wins!"
#define MSG_TIE    "Tie game."

#include <QDebug>
#include "Utils.h"

Game::Game() :
    turnPiece_(PIECE_TYPE_NONE)
  , winner_(PIECE_TYPE_NONE)
{
}

void Game::init()
{
    board.clearPieces();
    turnPiece_ = PIECE_TYPE_X;

    QString msg = MSG_TURN_X;
    emit update_msg_label(msg);
}

void Game::start(Player pX, Player pO)
{
    playerX = pX;
    playerO = pO;

    init();
    emit gameInit(playerX, playerO);
}

bool Game::getActive()
{
    return turnPiece_ != PIECE_TYPE_NONE;
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
        turnPiece_ = PIECE_TYPE_NONE;
        emit gameEnded(winner);
    }
}

void Game::placePiece(Cell cell)
{
    if (board.getPiece(cell) == PIECE_TYPE_NONE) // valid move
    {
        // Place piece
        board.setPiece(cell, turnPiece_);
        turnPiece_ = Utils::opponentPiece(turnPiece_);

        emit gameStateUpdated(playerX, playerO, board);

        QString msg = MSG_TURN_X;
        if (turnPiece_ == PIECE_TYPE_O) msg = MSG_TURN_O;
        emit update_msg_label(msg);
    }
}

void Game::quit(PieceType quittingPiece)
{
    turnPiece_ = PIECE_TYPE_NONE;
    winner_ = Utils::opponentPiece(quittingPiece);
    emit gameEnded(winnerPlayer());
}

Player Game::getPlayerX()
{
    return playerX;
}

Player Game::getPlayerO()
{
    return playerO;
}

Player Game::winnerPlayer()
{
    if (winner_ == PIECE_TYPE_O)
    {
        return playerO;
    }
    else if (winner_ == PIECE_TYPE_X)
    {
        return playerX;
    }
    return Player();
}

PieceType Game::currentTurnPiece()
{
    return turnPiece_;
}

