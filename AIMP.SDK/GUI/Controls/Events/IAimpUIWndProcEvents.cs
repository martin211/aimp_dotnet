namespace AIMP.SDK.GUI.Controls.Events
{
    using AIMP.SDK.Annotations;

    public interface IAimpUIWndProcEvents
    {
        event AimpBoolUIEventHandler<AimpBeforeWndProcArgs> OnBeforeWndProc;

        event AimpUIEventHandler<AimpAfterWndProcArgs> OnAfterWndProc;
    }
}