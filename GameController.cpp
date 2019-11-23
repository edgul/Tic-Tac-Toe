#include "GameController.h"

GameController::GameController()
{
    connect(&tcp_server, SIGNAL(received_data(QString)), SLOT(onReceivedData(QString)));
}

void GameController::onReceivedData(QString data)
{

    // unpack the data

    // make a decision

}
