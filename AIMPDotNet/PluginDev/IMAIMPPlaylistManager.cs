using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Works with playlists
    /// </summary>
    public interface IMAIMPPlaylistManager
    {
        /// <summary>
        /// Load new playlist from file to player
        /// </summary>
        /// <param name="FileName">Path to playlist file</param>
        /// <param name="SetActive">If true, sets as active playlist after loading</param>
        /// <param name="PlayIt">If true, begins playing after load</param>
        /// <returns>Loaded playlist</returns>
        MAIMPConnectedPlaylist CreateFromFile(String FileName, Boolean SetActive, Boolean PlayIt);
        /// <summary>
        /// Creates empty playlist
        /// </summary>
        /// <param name="Name">Name of new playlist</param>
        /// <param name="SetActive">If true, sets new playlist as active</param>
        /// <returns>Created playlist</returns>
        MAIMPConnectedPlaylist CreateEmpty(String Name, Boolean SetActive);
        /// <summary>
        /// Remove playlist by index inside player
        /// </summary>
        /// <param name="ID">Position of playlist</param>
        /// <returns>Success</returns>
        Boolean RemoveAt(Int32 ID);
        /// <summary>
        /// Remove concrete playlist from player
        /// </summary>
        /// <param name="pls">Playlist</param>
        /// <returns>Success</returns>
        Boolean Remove(MAIMPConnectedPlaylist pls);

        /// <summary>
        /// Save playlist to file
        /// </summary>
        /// <param name="pls">Playlist</param>
        /// <param name="FileName">Path to file</param>
        void SavePlaylistToFile(IMAIMPPlaylist pls, String FileName);
        /// <summary>
        /// Load tracks to playlist form playlist file
        /// </summary>
        /// <param name="pls">Playlist</param>
        /// <param name="FileName">Path to playlist file</param>
        void LoadItemsToPlaylistFormFile(IMAIMPPlaylist pls, String FileName);

        /// <summary>
        /// Number of playlists inside player
        /// </summary>
        Int32 Count { get; }
        /// <summary>
        /// Returns playlist inside player by position
        /// </summary>
        /// <param name="ID">Position of playlist inside player</param>
        /// <returns>Playlist</returns>
        MAIMPConnectedPlaylist this[Int32 ID] { get; }
        /// <summary>
        /// Returns playlist inside player by name
        /// </summary>
        /// <param name="Name">Name of playlist</param>
        /// <returns>Playlist</returns>
        MAIMPConnectedPlaylist this[string Name] { get; }
        /// <summary>
        /// Gets of sets currently active playlist
        /// </summary>
        MAIMPConnectedPlaylist ActivePlaylist { get; set; }
        /// <summary>
        /// Gets of sets currently playing playlist
        /// </summary>
        MAIMPConnectedPlaylist PlayingPlaylist { get; set; }

        /// <summary>
        /// Detemines existence of playlist with particular name
        /// </summary>
        /// <param name="Name">Name of playlist</param>
        /// <returns>Existence</returns>
        bool IsExist(string Name);

        /// <summary>
        /// Add disconnected playlist to player
        /// </summary>
        /// <param name="pls">Disconnected playlist</param>
        /// <param name="SetActive">If true, sets added playlist as active</param>
        /// <param name="PlayIt">If true, plays added playlist</param>
        /// <param name="UpdateTags">if true, reloads information for all tracks insode playlist</param>
        /// <returns>Added playlist</returns>
        MAIMPConnectedPlaylist Connect(MAIMPDisconnectedPlaylist pls, Boolean SetActive, Boolean PlayIt, Boolean UpdateTags);
        /// <summary>
        /// Creates disconnected playlist from connected
        /// </summary>
        /// <param name="pls">Playlist inside player</param>
        /// <param name="NeedRemove">If true, removes original playlist from player</param>
        /// <returns>Disconnected playlist</returns>
        MAIMPDisconnectedPlaylist Disconnect(MAIMPConnectedPlaylist pls, Boolean NeedRemove);
        /// <summary>
        /// Copy tracks information from playlist inside player to disconnected playlist
        /// </summary>
        /// <param name="outDat">Disconnected playlist</param>
        /// <param name="pls">Connected playlist</param>
        /// <param name="NeedRemove">If true, removes original playlist from player</param>
        void Disconnect(MAIMPDisconnectedPlaylist outDat, MAIMPConnectedPlaylist pls, Boolean NeedRemove);

        /// <summary>
        /// Plays particualr file inside playlist
        /// </summary>
        /// <param name="Pls">Playlist</param>
        /// <param name="FileID">Position of the file inside it</param>
        void PlayFile(MAIMPConnectedPlaylist Pls, int FileID);
        /// <summary>
        /// Plays particualr file inside playlist
        /// </summary>
        /// <param name="PlsID">Playlist ID</param>
        /// <param name="FileID">Position of the file inside it</param>
        void PlayFile(int PlsID, int FileID);


    }
}
