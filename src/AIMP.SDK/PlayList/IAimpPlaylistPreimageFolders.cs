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

namespace AIMP.SDK.Playlist
{
    public interface IAimpPlaylistPreimageFolders : IAimpPlaylistPreimage
    {
        ActionResultType ItemsAdd(string path, bool recursive);

        ActionResultType ItemsDelete(int index);

        ActionResultType ItemsDeleteAll();

        ActionResultType ItemsGet(int index, out string path, out bool recursive);

        int ItemsGetCount();
    }
}