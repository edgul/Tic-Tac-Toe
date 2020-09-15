#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
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
    void onGamePlayWidgetClickedValidQuad(Quad quad);

private:
    Ui::ClientMainWindow *ui;

    WelcomeWidget *welcomeWidget_;
    SelectDifficultyWidget *selectDifficultyWidget_;
    GamePlayWidget *gamePlayWidget_;
};

#endif // CLIENTMAINWINDOW_H
