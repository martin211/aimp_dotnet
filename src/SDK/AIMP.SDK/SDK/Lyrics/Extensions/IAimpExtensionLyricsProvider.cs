using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Lyrics.Objects;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Lyrics.Extensions;

/// <summary>
/// Interface IAimpExtensionLyricsProvider
/// Implements the <see cref="AIMP.SDK.IAimpExtension" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpExtension" />
public interface IAimpExtensionLyricsProvider : IAimpExtension
{
    /// <summary>
    /// Gets the category.
    /// </summary>
    /// <value>The category.</value>
    LyricsProviderCategory Category { get; }

    /// <summary>
    /// Gets the specified owner.
    /// </summary>
    /// <param name="owner">The owner.</param>
    /// <param name="fileInfo">The file information.</param>
    /// <param name="flags">The flags.</param>
    /// <param name="lyrics">The lyrics.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Get(IAimpTaskOwner owner, IAimpFileInfo fileInfo, LyricsFlags flags, IAimpLyrics lyrics);
}