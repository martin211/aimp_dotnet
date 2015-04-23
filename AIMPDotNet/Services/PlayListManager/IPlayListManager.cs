﻿using System.Collections.Generic;

namespace AIMP.SDK.Services.PlayListManager
{
    public interface IPlayListManager
    {
        IAimpPlayList CreatePlaylist(string name, bool isActive);

        IAimpPlayList CreatePlaylistFromFile(string fileName, bool isActive);

        IAimpPlayList GetActivePlaylist();

        void SetActivePlaylist(IAimpPlayList playList);

        IAimpPlayList GetPlayablePlaylist();

        IAimpPlayList GetLoadedPlaylist(int index);

        IAimpPlayList GetLoadedPlaylistById(string id);

        IAimpPlayList GetLoadedPlaylistByName(string name);

        int GetLoadedPlaylistCount();
    }
}