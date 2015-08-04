#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfo>
#include <QMainWindow>
#include <QTime>
#include <phonon/MediaSource>

void delay(int millisecondsToWait);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool autoRestart;
    const int AUTO_RESTART_DELAY = 3000;
    const std::string GAME_EXECUTABLE = "Cycleshooter";

private slots:
    void launchGame() const;
    void on_checkBoxAutoRestart_stateChanged(int arg1);
    void on_pushButtonPlayPause_clicked();
};

#endif // MAINWINDOW_H
