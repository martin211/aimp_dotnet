// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.Playback
{
    public delegate bool AimpCheckUrl(ref string url);

    public interface IAimpExtensionPlayerHook
    {
        event AimpCheckUrl OnCheckURL;
    }
}