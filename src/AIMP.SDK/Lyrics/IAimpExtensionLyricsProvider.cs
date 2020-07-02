// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK.FileManager;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Lyrics
{
    public enum LyricsProviderCategory
    {
        File,
        Internet
    }

    public interface IAimpExtensionLyricsProvider : IAimpExtension
    {
        LyricsProviderCategory Category { get; }

        AimpActionResult Get(IAimpTaskOwner owner, IAimpFileInfo fileInfo, LyricsFlags flags, IAimpLyrics lyrics);
    }
}