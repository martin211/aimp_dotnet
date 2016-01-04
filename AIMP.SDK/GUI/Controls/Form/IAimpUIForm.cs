namespace AIMP.SDK.GUI.Controls.Form
{
    using System;

    [Flags]
    public enum AimpBorderIcon
    {
        AIMPUI_FLAGS_BORDERICON_SYSTEMMENU,
        AIMPUI_FLAGS_BORDERICON_MINIMIZE,
        AIMPUI_FLAGS_BORDERICON_MAXIMIZE
    }

    public enum AimpBorderStyle
    {
        AIMPUI_FLAGS_BORDERSTYLE_SIZEABLE,
        AIMPUI_FLAGS_BORDERSTYLE_SINGLE,
        AIMPUI_FLAGS_BORDERSTYLE_DIALOG,
        AIMPUI_FLAGS_BORDERSTYLE_TOOLWINDOW,
        AIMPUI_FLAGS_BORDERSTYLE_TOOLWINDOWSIZABLE,
        AIMPUI_FLAGS_BORDERSTYLE_NONE
    }

    public enum AimpModalResult
    { }

    public interface IAimpUIForm : IAimpUIWinControl, IAimpUIFormEvents
    {
        string Caption { get; set; }

        AimpBorderIcon AimpBorderIcons { get; set; }

        AimpBorderStyle AimpBorderStyle { get; set; }

        IntPtr Icon { get; set; }

        bool ShowTasksBar { get; set; }

        bool CloseByEscape { get; set; }

        int Padding { get; set; }

        AimpActionResult Close();

        AimpActionResult GetFocusedControl(out IAimpUIWinControl control);

        AimpActionResult Localized();

        AimpActionResult Release(bool postponed);

        AimpModalResult ShowModal();
    }
}