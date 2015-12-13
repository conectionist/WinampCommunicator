using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace WinampRemoteCommander
{
    public partial class Form1 : Form
    {
        private AsyncServer server;
        private Thread serverThread;

        public Form1()
        {
            InitializeComponent();

            server = new AsyncServer();

            serverThread = new Thread(new ThreadStart(server.StartListening));
        }

        private async void Form1_Load(object sender, EventArgs e)
        {
            IconSetup();

            // the .NET framework (at least until version 4.5) language does not allow an application 
            // to start directly in the tray (without showing the main window)
            // it has to be show at least for a fraction of a second
            // unfortunately, simply adding Hide() in the Load function has no effect whatsoever
            // we have to wait a few miliseconds and then call the Hide() method
            await WaitForHidingMainWindow();

            Hide();

            StartReceivingRemoteCommands();
        }

        protected void IconSetup()
        {
            notifyIcon.Icon = AllResources.winamp_remote_commander;
            notifyIcon.Text = "Winamp Remote Commander";

            notifyIcon.ContextMenuStrip = contextMenuStripTrayIcon;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            server.SignalShutdown();

            Application.Exit();
        }

        private async Task WaitForHidingMainWindow()
        {
            await Task.Delay(10);
        }

        private void StartReceivingRemoteCommands()
        {
            serverThread.Start();
        }
    }
}
