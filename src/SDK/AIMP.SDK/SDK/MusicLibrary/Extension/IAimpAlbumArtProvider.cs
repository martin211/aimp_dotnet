using AIMP.SDK.Objects;

namespace AIMP.SDK.MusicLibrary.Extension;

public interface IAimpAlbumArtProvider
{
    AimpActionResult<IAimpImageContainer> Get(IAimpObjectList<string> fields, object[] values, IAimpPropertyList options);
}