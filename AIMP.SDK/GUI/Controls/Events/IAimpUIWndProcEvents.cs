namespace AIMP.SDK.GUI.Controls.Events
{
    public interface IAimpUIWndProcEvents
    {
        event AimpBoolUIControlEventHandler<AimpBeforeWndProcArgs> OnBeforeWndProc;

        event AimpUIControlEventHandler<AimpAfterWndProcArgs> OnAfterWndProc;
    }
}