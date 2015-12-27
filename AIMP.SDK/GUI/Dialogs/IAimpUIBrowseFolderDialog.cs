namespace AIMP.SDK.GUI.Dialogs
{
    using System;
    using System.Collections.Generic;

    [Flags]
    public enum FolderDialogFlags
    {
        
    }

    public interface IAimpUIBrowseFolderDialog
    {
        IEnumerable<string> Execute(IntPtr parentWindow, FolderDialogFlags flags, string defaultPath);
    }
}