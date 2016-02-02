namespace AIMP.SDK.GUI.Controls
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIScrollBox : IAimpUIWinControl
    {
        AimpBorders Borders { get; set; }

        AimpActionResult MakeVisible(IAimpUIControl control);
    }
}