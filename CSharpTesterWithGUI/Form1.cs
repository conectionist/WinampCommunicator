using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CSharpTesterWithGUI
{
    public partial class Form1 : Form
    {
        private WinampCommunicator wc;
        
        public Form1()
        {
            InitializeComponent();

            wc = new WinampCommunicator();

            UpdateTrackName();
        }

        private void buttonPrevious_Click(object sender, EventArgs e)
        {
            wc.PreviousTrack();

            UpdateTrackName();
        }

        private void buttonPlay_Click(object sender, EventArgs e)
        {
            wc.Play();

            UpdateTrackName();
        }

        private void buttonPause_Click(object sender, EventArgs e)
        {
            wc.Pause();

            UpdateTrackName();
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            wc.Stop();

            UpdateTrackName();
        }

        private void buttonNext_Click(object sender, EventArgs e)
        {
            wc.NextTrack();

            UpdateTrackName();
        }

        private void volumeBar_ValueChanged(object sender, EventArgs e)
        {
            int percent = volumeBar.Value;

            labelVolume.Text = "Volume: " + percent + "%";
            wc.SetVolume((uint)percent);
        }

        private void buttonVolumeDown_Click(object sender, EventArgs e)
        {
            wc.LowerVolume();
        }

        private void buttonVolumeUp_Click(object sender, EventArgs e)
        {
            wc.RaiseVolume();
        }

        private void UpdateTrackName()
        {
            string currentTrackName = wc.GetCurrentTrackName().ToString();

            labelCurrentTrackName.Text = "Current track: \n" + currentTrackName;
        }

        private void buttonRefreshTitle_Click(object sender, EventArgs e)
        {
            UpdateTrackName();
        }
    }
}
