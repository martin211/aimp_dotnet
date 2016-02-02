namespace AIMP.SDK.GUI.Controls.Events
{
    // ReSharper disable once InconsistentNaming
    public delegate void AimpUIControlEventHandler(IAimpUIControl sender);

    // ReSharper disable once InconsistentNaming
    public delegate void AimpUIControlEventHandler<in TAimpEventArgs>(IAimpUIControl sender, TAimpEventArgs args);

    // ReSharper disable once InconsistentNaming
    public delegate bool AimpBoolUIControlEventHandler(IAimpUIControl sender);

    // ReSharper disable once InconsistentNaming
    public delegate bool AimpBoolUIControlEventHandler<in TAimpEventArgs>(IAimpUIControl sender, TAimpEventArgs args);

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TAimpEventArgs">The type of the aimp event arguments.</typeparam>
    /// <param name="sender">The sender.</param>
    /// <param name="args">The <see cref="TAimpEventArgs"/> instance containing the event data.</param>
    // ReSharper disable once InconsistentNaming
    public delegate void AimpUIWinControlEventHandler<in TAimpEventArgs>(IAimpUIWinControl sender, TAimpEventArgs args);
}
