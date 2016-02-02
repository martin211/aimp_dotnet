using AIMP.SDK.GUI.Controls.Events;

namespace AIMP.SDK.GUI.Controls.PageControl
{
    public interface IAimpUIPageControlEvents
    {
        AimpUIWinControlEventHandler<AimpPageControlEventArgs> OnActivating(IAimpUIPageControl sender, AimpPageControlEventArgs args);

        AimpUIWinControlEventHandler<AimpPageControlEventArgs> OnActivated(IAimpUIPageControl sender, AimpPageControlEventArgs args);
    }
}