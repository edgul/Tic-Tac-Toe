#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include "AI.h"
#include "widgets/WelcomeWidget.h"
#include "widgets/SelectDifficultyWidget.h"
#include "widgets/GamePlayWidget.h"

namespace Ui {
class ClientMainWindow;
}

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QWidget *parent = nullptr);
    ~ClientMainWindow();

private slots:
    void onWelcomeWidgetClickedSinglePlayer();
    void onWelcomeWidgetClickedMultiPlayer();

    void onSelectDifficultyWidgetClickedOk();
    void onSelectDifficultyWidgetClickedCancel();

    void onGamePlayWidgetClickedLeave();
    void onGamePlayWidgetClickedValidCell(Cell cell);

private:
    Ui::ClientMainWindow *ui;

    enum GameMode { GAME_MODE_INIT, GAME_MODE_SINGLE, GAME_MODE_MULTI };
    GameMode gameMode_;

    WelcomeWidget *welcomeWidget_;
    SelectDifficultyWidget *selectDifficultyWidget_;
    GamePlayWidget *gamePlayWidget_;
    AI ai_;

    void singlePlayerLogic(Cell cell);
    void endGame(PieceType winner);


};

#endif // CLIENTMAINWINDOW_H
