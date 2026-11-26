using System;

namespace AIMP.SDK;

/// <summary>
/// AIMP plugin interface.
/// Implements the <see cref="System.IDisposable" />
/// </summary>
/// <seealso cref="System.IDisposable" />
public interface IAimpPlugin : IDisposable
{
    /// <summary>
    /// Initializes this instance.
    /// </summary>
    void Initialize();
}