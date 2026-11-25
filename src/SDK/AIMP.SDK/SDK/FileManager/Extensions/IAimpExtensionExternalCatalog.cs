using System;
using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager.Extensions;

/// <summary>
/// External catalog displayed in the file manager (AIMP 6.0+).
/// Replaces the deprecated album art catalog extensions.
/// </summary>
public interface IAimpExtensionExternalCatalog : IAimpExtension
{
    AimpActionResult<IAimpImageContainer> GetIcon();

    AimpActionResult<string> GetName();

    AimpActionResult Show(IntPtr ownerWindow, object data);
}