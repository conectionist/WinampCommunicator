#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSystemTrayIcon;
class QMenu;
class QAction;
class QTcpServer;
class QTcpSocket;

class WinampCommunicator;

enum WinampCommand
{
    WinampCmd_Invalid,
    WinampCmd_Previous,
    WinampCmd_Play,
    WinampCmd_Pause,
    WinampCmd_Stop,
    WinampCmd_Next,
    WinampCmd_VolumeUp,
    WinampCmd_VolumeDown,
    WinampCmd_SetVolume,
    WinampCmd_CurrentTrack
};

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

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    QAction* quitAction;

    QTcpServer* server;

    WinampCommunicator* m_pWinampCommunicator;

private slots:
    void newConnection();
    void OnNewCommand();

protected:
    WinampCommand TranslateReceivedMessageIntoCommand(QString message);
    QString HandleCommand(const QString& message);
};

#endif // MAINWINDOW_H
