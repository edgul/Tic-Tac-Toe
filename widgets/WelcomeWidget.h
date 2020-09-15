#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();

private slots:
    void on_buttonSinglePlayer_clicked();
    void on_buttonMultiPlayer_clicked();

signals:
    void clickedSinglePlayer();
    void clickedMultiPlayer();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
