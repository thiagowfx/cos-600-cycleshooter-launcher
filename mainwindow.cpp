#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchGame() const {
    ui->statusBar->showMessage("Launching the game...");
    system("./launch.sh");
    ui->statusBar->showMessage("Game launched.");

    if(autoRestart) {
        ui->statusBar->showMessage("Will relaunch the game in a few seconds.");
        delay(AUTO_RESTART_DELAY);

        if(this->isVisible()) {
            launchGame();
        }
    }
}

void MainWindow::on_checkBoxAutoRestart_stateChanged(int arg1) {
    switch(arg1) {
    case Qt::Unchecked:
        autoRestart = false;
        break;
    case Qt::Checked:
    default:
        autoRestart = true;
        break;
    }
}


void delay(int millisecondsToWait) {
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
