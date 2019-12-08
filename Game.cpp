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
    board.clear();
    turn_x = true;

    QString msg = MSG_TURN_X;
    emit update_msg_label(msg);
    active_ = true;
}

void Game::startMultiplayer(Player p1, Player p2)
{
    // TODO: game should decide who is what

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

void Game::startSinglePlayer(Difficulty difficulty)
{
    init();

    ai.set_piece_type(PLAYER_O);
    ai.set_difficulty(difficulty);

    singlePlayer = true;
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
    if (board.winner() == PLAYER_X) // x wins
    {
        QString msg = MSG_WIN_X;
        emit update_msg_label(msg);

        winner = playerX;
        game_over = true;

    }
    else if (board.winner() == PLAYER_O) // o wins
    {
        QString msg = MSG_WIN_O;
        emit update_msg_label(msg);
        winner = playerO;

        game_over = true;
    }
    else if (board.full()) // tie
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

        // disable user input for one player game
//        active = true;
//        if (singlePlayer)
//        {
//            if (!turn_x)
//            {
//                active = false;
//            }
//        }
    }
}

void Game::placePiece(Player player, Quad quad)
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
            if (board.quad_empty(quad)) // valid move
            {
                // Place piece
                QString piece = get_turn_piece();
                board.place(piece, quad);
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

void Game::ai_goes()
{
    QString ai_piece = ai.get_piece();
    Quad ai_move = ai.get_move(board);

    board.place(ai_piece, ai_move);

    checkForGameOver();
}

QString Game::get_turn_piece()
{
    QString turn_piece;
    if (turn_x)
    {
        turn_piece = PLAYER_X;
    }
    else
    {
        turn_piece = PLAYER_O;
    }

    return turn_piece;
}

