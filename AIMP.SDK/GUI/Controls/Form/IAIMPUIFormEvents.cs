namespace AIMP.SDK.GUI.Controls.Form
{
    using AIMP.SDK.GUI.Controls.Events;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIFormEvents
    {
        event AimpUIControlEventHandler OnActivated;

        event AimpUIControlEventHandler OnDeactivated;

        event AimpUIControlEventHandler OnCreated;

        event AimpUIControlEventHandler OnDestroyed;

        event AimpUIControlEventHandler<AimpFormCloseQueryArgs> OnCloseQuery;

        event AimpUIControlEventHandler OnLocalize;

        event AimpUIControlEventHandler<AimpFormShortCutArgs> OnShortCut;
    }
}