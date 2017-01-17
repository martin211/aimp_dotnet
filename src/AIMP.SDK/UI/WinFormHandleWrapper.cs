using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.CSharpMixingLibrary
{
    public struct WinFormHandleWrapper : System.Windows.Forms.IWin32Window
    {
        public WinFormHandleWrapper(IntPtr Wnd)
        {
            _hndl = Wnd;
        }

        public IntPtr Handle
        {
            get
            {
                return _hndl;
            }
        }
        private IntPtr _hndl;
    }
}
