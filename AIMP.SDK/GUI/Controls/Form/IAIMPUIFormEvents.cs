namespace AIMP.SDK.GUI.Controls.Form
{
    using AIMP.SDK.GUI.Controls.Events;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIFormEvents
    {
        event AimpUIEventHandler OnActivated;

        event AimpUIEventHandler OnDeactivated;

        event AimpUIEventHandler OnCreated;

        event AimpUIEventHandler OnDestroyed;

        event AimpUIEventHandler<AimpFormCloseQueryArgs> OnCloseQuery;

        event AimpUIEventHandler OnLocalize;

        event AimpUIEventHandler<AimpFormShortCutArgs> OnShortCut;
    }
}