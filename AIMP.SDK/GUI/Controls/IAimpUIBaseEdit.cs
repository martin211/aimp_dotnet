namespace AIMP.SDK.GUI.Controls
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIBaseEdit : IAimpUIWinControl
    {
        bool Borders { get; set; }

        int MaxLength { get; set; }

        bool ReadOnly { get; set; }

        int SelStart { get; set; }

        int SelLength { get; set; }

        string SelText { get; set; }

        string Text { get; set; }

        AimpActionResult CopyToClipboard();

        AimpActionResult CutToClipboard();

        AimpActionResult PasteFromClipboard();

        AimpActionResult SelectAll();

        AimpActionResult SelectNone();
    }
}