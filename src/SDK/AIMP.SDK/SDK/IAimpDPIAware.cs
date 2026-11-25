namespace AIMP.SDK;

public interface IAimpDPIAware : IAimpObject
{
    /// <summary>
    /// Gets or sets the dpi.
    /// </summary>
    /// <value>The dpi.</value>
    int DPI { get; set; }
}