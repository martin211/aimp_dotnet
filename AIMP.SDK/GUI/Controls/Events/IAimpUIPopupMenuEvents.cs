namespace AIMP.SDK.GUI.Controls.Events
{
    public delegate bool AimpContextPopupHandler(IAimpUIControl sender, AimpContextPopupEventArgs args);

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIPopupMenuEvents
    {
        event AimpContextPopupHandler OnContextPopup;
    }
}