#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H

#include <QWidget>

namespace Ui {
class MainWindowManager;
}

class MainWindowManager : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowManager(QWidget *parent = 0);
    ~MainWindowManager();

private slots:
    void on_button_new_main_window_clicked();

private:
    Ui::MainWindowManager *ui;
};

#endif // MAINWINDOWMANAGER_H
