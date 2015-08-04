#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Idle.");
    ui->videoPlayer->load(Phonon::MediaSource(QUrl::fromLocalFile(QFileInfo("just_do_it.mp4").absoluteFilePath())));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchGame() const {
    ui->statusBar->showMessage("Launching the game...");
    std::string launchCommand = "./" + GAME_EXECUTABLE + " " + ui->lineEditArguments->text().toStdString();
    system(launchCommand.c_str());
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

void MainWindow::on_pushButtonPlayPause_clicked() {
    static bool isPlaying = false;
    isPlaying ? ui->videoPlayer->pause() : ui->videoPlayer->play();
    isPlaying = !isPlaying;
}
