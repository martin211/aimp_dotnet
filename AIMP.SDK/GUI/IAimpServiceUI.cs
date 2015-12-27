namespace AIMP.SDK.GUI
{
    using System;

    using AIMP.SDK.UI;

    [Flags]
    public enum CreateFormFlags
    {
        
    }

    public interface IAimpServiceUI
    {
        AimpActionResult CreateForm(IntPtr ownerWindow, CreateFormFlags flags, string name, out IAimpUIForm form);

        AimpActionResult CreateControl(IAimpUIForm owner, IAimpUIWinControl parent, string name, out AimpUIItem item);

        AimpActionResult CreateObject(IAimpUIForm owner, out AimpUIItem item);
    }
}