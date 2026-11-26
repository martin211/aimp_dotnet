using AIMP.SDK.Lyrics.Objects;

namespace AIMP.SDK.Lyrics;

/// <summary>
/// Delegate AimpServiceLyricsReceive
/// </summary>
/// <param name="lyrics">The lyrics.</param>
/// <param name="userData">The user data.</param>
public delegate void AimpServiceLyricsReceive(IAimpLyrics lyrics, string userData);