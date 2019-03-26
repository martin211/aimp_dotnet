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
namespace AIMP.SDK.Playlist
{
    public interface IAimpPlaylistPreimageFolders : IAimpPlaylistPreimage
    {
        AimpActionResult ItemsAdd(string path, bool recursive);

        AimpActionResult ItemsDelete(int index);

        AimpActionResult ItemsDeleteAll();

        AimpActionResult ItemsGet(int index, out string path, out bool recursive);

        int ItemsGetCount();
    }
}