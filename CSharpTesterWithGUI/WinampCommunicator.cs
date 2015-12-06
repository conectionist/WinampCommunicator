using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices; 

namespace CSharpTesterWithGUI
{
    class WinampBridge
    {
        [DllImport("WinampCppBridge.dll")]
        public static extern void PreviousTrack();

        [DllImport("WinampCppBridge.dll")]
        public static extern void Play();

        [DllImport("WinampCppBridge.dll")]
        public static extern void Pause();

        [DllImport("WinampCppBridge.dll")]
        public static extern void Stop();

        [DllImport("WinampCppBridge.dll")]
        public static extern void NextTrack();

        [DllImport("WinampCppBridge.dll")]
        public static extern void RaiseVolume(uint percent);

        [DllImport("WinampCppBridge.dll")]
        public static extern void LowerVolume(uint percent);

        [DllImport("WinampCppBridge.dll")]
        public static extern void SetVolume(uint percent);

        [DllImport("WinampCppBridge.dll")]
        public static extern string GetCurrentTrackName();
    }

    class WinampCommunicator
    {
        public void PreviousTrack()
        {
            WinampBridge.PreviousTrack();
        }

        public void Play()
        {
            WinampBridge.Play();
        }

        public void Pause()
        {
            WinampBridge.Pause();
        }

        public void Stop()
        {
            WinampBridge.Stop();
        }

        public void NextTrack()
        {
            WinampBridge.NextTrack();
        }

        public void RaiseVolume(uint percent = 1)
        {
            WinampBridge.RaiseVolume(percent);
        }

        public void LowerVolume(uint percent = 1)
        {
            WinampBridge.LowerVolume(percent);
        }

        public void SetVolume(uint percent)
        {
            WinampBridge.SetVolume(percent);
        }

        public string GetCurrentTrackName()
        {
            return WinampBridge.GetCurrentTrackName();
        }
    }
}
