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
//    else
//        trayIcon->showMessage("Server started",
//                              "Winamp remote commander is up and running",
//                              QSystemTrayIcon::Information,
//                              2000);
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
        HandleCommand(msg);
    }
}

WinampCommand MainWindow::TranslateReceivedMessageIntoCommand(QString msg)
{
    if(msg.endsWith("\n"))
        msg.remove("\n");

    if(msg.endsWith("\r"))
        msg.remove("\r");

    if (msg == "z")
        return WinampCmd_Previous;
    else if (msg == "x")
        return WinampCmd_Play;
    else if (msg == "c")
        return WinampCmd_Pause;
    else if (msg == "v")
        return WinampCmd_Stop;
    else if (msg == "b")
        return WinampCmd_Next;
    else
        return WinampCmd_Invalid;
}

void MainWindow::HandleCommand(const QString &message)
{
    trayIcon->showMessage("New Message", message);

    WinampCommand cmd = TranslateReceivedMessageIntoCommand(message);

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
        case WinampCmd_Invalid:
        default:
            trayIcon->showMessage("Error: Unknown message", message, QSystemTrayIcon::Critical);
            break;
        }
    }
    catch (const NotRunningException& nrex)
    {
        trayIcon->showMessage("Error", nrex.GetErrorMessage().c_str(), QSystemTrayIcon::Critical);
    }
}
