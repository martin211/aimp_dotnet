namespace AIMP.SDK.GUI.Controls
{
    using AIMP.SDK.GUI.Controls.Events;
    public interface IAimpUIEditButton : IAimpUIChangeEvents
    {
        string Custom { get; set; }

        string Caption { get; set; }

        bool Enabled { get; set; }

        string Hint { get; set; }

        int Index { get; set; }

        int ImageIndex { get; set; }

        bool Visible { get; set; }

        string Width { get; set; }
    }
}