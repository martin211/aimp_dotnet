namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIPopupMenuEvents
    {
        event AimpBoolUIControlEventHandler<AimpContextPopupArgs> OnContextPopup;
    }
}