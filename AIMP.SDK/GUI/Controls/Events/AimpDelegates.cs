namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public delegate void AimpUIEventHandler(IAimpUIControl sender);

    // ReSharper disable once InconsistentNaming
    public delegate void AimpUIEventHandler<TAimpEventArgs>(IAimpUIControl sender, TAimpEventArgs args);

    // ReSharper disable once InconsistentNaming
    public delegate bool AimpBoolUIEventHandler(IAimpUIControl sender);

    // ReSharper disable once InconsistentNaming
    public delegate bool AimpBoolUIEventHandler<TAimpEventArgs>(IAimpUIControl sender, TAimpEventArgs args);
}
