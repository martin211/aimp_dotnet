namespace AIMP.SDK.GUI
{
    using System;

    using AIMP.SDK.GUI.Controls;
    using AIMP.SDK.GUI.Controls.Form;
    using AIMP.SDK.UI;

    [Flags]
    public enum CreateFormFlags
    {
        None = 0,
        AIMPUI_SERVICE_CREATEFORM_FLAGS_CHILD
    }

    // ReSharper disable once InconsistentNaming
    public interface IAimpServiceUI
    {
        AimpActionResult CreateForm(IntPtr ownerWindow, CreateFormFlags flags, string name, out IAimpUIForm form);

        AimpActionResult CreateControl(IAimpUIForm owner, IAimpUIWinControl parent, string name, out AimpUIItem item);

        AimpActionResult CreateObject(IAimpUIForm owner, out AimpUIItem item);
    }
}