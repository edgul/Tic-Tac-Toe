#ifndef GAME_H
#define GAME_H

#include "BoardWidget.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void set_board(BoardWidget * board_widget);

    void start();

signals:
    void update_msg_label(QString msg);

private slots:
    void board_clicked(Quad quad);

private:
    BoardWidget * board_widget;

    bool turn_x;
    bool active;

};

#endif // GAME_H
