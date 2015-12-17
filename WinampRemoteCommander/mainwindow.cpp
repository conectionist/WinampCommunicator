#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTcpServer>
#include <QTcpSocket>

#include "WinampAPI/WinampCommunicator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    quitAction = new QAction("Exit", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(QIcon(":/res/icon.ico"),this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    m_pWinampCommunicator = new WinampCommunicator;

    server = new QTcpServer();
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 4567))
        trayIcon->showMessage("Error", "Server could not start",QSystemTrayIcon::Critical);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trayIcon;
    delete trayIconMenu;
    delete quitAction;
    delete server;

    delete m_pWinampCommunicator;
}

void MainWindow::newConnection()
{
    QTcpSocket* socket = server->nextPendingConnection();

    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(OnNewCommand()));
}

void MainWindow::OnNewCommand()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket == 0)
        return;

    if(socket->bytesAvailable())
    {
        QString msg = socket->readAll();
        QString response = HandleCommand(msg);

        socket->write(response.toUtf8());
    }
}

WinampCommand MainWindow::TranslateReceivedMessageIntoCommand(QString msg)
{
    if(msg.endsWith("\n"))
        msg.remove("\n");

    if(msg.endsWith("\r"))
        msg.remove("\r");

    switch(msg[0].toLatin1())
    {
    case 'z':
        return WinampCmd_Previous;
    case 'x':
        return WinampCmd_Play;
    case 'c':
        return WinampCmd_Pause;
    case 'v':
        return WinampCmd_Stop;
    case 'b':
        return WinampCmd_Next;
    case '+':
        return WinampCmd_VolumeUp;
    case '-':
        return WinampCmd_VolumeDown;
    case 's':
        return WinampCmd_SetVolume;
    case 't':
        return WinampCmd_CurrentTrack;
    default:
        return WinampCmd_Invalid;
    }
}

QString MainWindow::HandleCommand(const QString &message)
{
    WinampCommand cmd = TranslateReceivedMessageIntoCommand(message);
    QString response = "ok";

    try
    {
        switch (cmd)
        {
        case WinampCmd_Previous:
            m_pWinampCommunicator->PreviousTrack();
            break;
        case WinampCmd_Play:
            m_pWinampCommunicator->Play();
            break;
        case WinampCmd_Pause:
            m_pWinampCommunicator->Pause();
            break;
        case WinampCmd_Stop:
            m_pWinampCommunicator->Stop();
            break;
        case WinampCmd_Next:
            m_pWinampCommunicator->NextTrack();
            break;
        case WinampCmd_VolumeUp:
            m_pWinampCommunicator->RaiseVolume();
            break;
        case WinampCmd_VolumeDown:
            m_pWinampCommunicator->LowerVolume();
            break;
        case WinampCmd_SetVolume:
            m_pWinampCommunicator->SetVolume(message.mid(1).toInt());
            break;
        case WinampCmd_CurrentTrack:
            response = "t";
            response += m_pWinampCommunicator->GetCurrentTrackName().c_str();
            break;
        case WinampCmd_Invalid:
        default:
            trayIcon->showMessage("Error: Unknown message", message, QSystemTrayIcon::Critical, 3000);
            break;
        }
    }
    catch (const NotRunningException& nrex)
    {
        trayIcon->showMessage("Error", nrex.GetErrorMessage().c_str(), QSystemTrayIcon::Critical);
        response = "Not running";
    }

    return response;
}
