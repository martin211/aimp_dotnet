using AIMP.SDK.Objects;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Playlist custom properties (AIMP 6.0+).
/// </summary>
public interface IAimpPlaylistProperties : IAimpPropertyList2
{
    AimpActionResult<string> GetCustomValue(string name);

    AimpActionResult SetCustomValue(string name, string value);
}