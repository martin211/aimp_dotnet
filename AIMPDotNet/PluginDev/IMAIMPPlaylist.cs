using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Interface for AIMP playlists
    /// </summary>
    public interface IMAIMPPlaylist
    {
        /// <summary>
        /// Removes tracks, that match the filtering function
        /// </summary>
        /// <param name="filter">Filtering</param>
        void RemoveByFilter(Func<IMAIMPFileInfoReadOnly, bool> filter);
        /// <summary>
        /// Sort playlist based on ordering function
        /// </summary>
        /// <param name="filter">Ordering function</param>
        void SortByFilter(Func<IMAIMPFileInfoReadOnly, IMAIMPFileInfoReadOnly, int> filter);
        /// <summary>
        /// Perform reordering track in playlist
        /// </summary>
        /// <param name="SortType">Way of reordering</param>
        void Sort(AIMPPlaylistSortType SortType);
        /// <summary>
        /// Remove one track from playlist
        /// </summary>
        /// <param name="ID">Position of track</param>
        /// <returns>Success</returns>
        bool RemoveAt(int ID);
        /// <summary>
        /// Move track inside playlist
        /// </summary>
        /// <param name="FromId">Current position of track</param>
        /// <param name="ToId">New position</param>
        /// <returns>Success</returns>
        bool Move(int FromId, int ToId);
        /// <summary>
        /// Add new file to playlist
        /// </summary>
        /// <param name="FileName">Path to file</param>
        /// <returns>Success</returns>
        bool Add(string FileName);
        /// <summary>
        /// Add new track to playlist
        /// </summary>
        /// <param name="finf">Information about track</param>
        /// <returns>Success</returns>
        bool Add(IMAIMPFileInfoReadOnly finf);
        /// <summary>
        /// Add several tracks to playlist
        /// </summary>
        /// <param name="Files">Paths to files</param>
        void AddRange(IEnumerable<string> Files);
        /// <summary>
        /// Add several track to playlist
        /// </summary>
        /// <param name="Files">Inforamtion about tracks</param>
        void AddRange(IEnumerable<IMAIMPFileInfoReadOnly> Files);
        /// <summary>
        /// Insert file to playlist
        /// </summary>
        /// <param name="Pos">Position of new file</param>
        /// <param name="FileName">Path to file</param>
        /// <returns>Success</returns>
        bool Insert(int Pos, string FileName);
        /// <summary>
        /// Insert track to playlist
        /// </summary>
        /// <param name="Pos">Position of new track</param>
        /// <param name="finf">Information about track</param>
        /// <returns>Success</returns>
        bool Insert(int Pos, IMAIMPFileInfoReadOnly finf);
        /// <summary>
        /// Clear playlist
        /// </summary>
        void Clear();

        /// <summary>
        /// Return title of track inside playlist
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Title</returns>
        string GetTrackTitle(int ID);

        /// <summary>
        /// Return path to track file
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Path to file</returns>
        string GetTrackFileName(int ID);
        /// <summary>
        /// Set new path for particular track inside playlist (change only track, not information)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New path</param>
        void SetTrackFileName(int ID, string Val);

        /// <summary>
        /// Return information about particular track
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Information about track</returns>
        MAIMPFileInfo GetTrackInformation(int ID);
        /// <summary>
        /// Set track information for particular file inside playlist (can change the path to track)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New information</param>
        void SetTrackInformation(int ID, IMAIMPFileInfoReadOnly Val);
        /// <summary>
        /// Set track information except path for particular file inside playlist.
        /// (Change only tags info)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="finf">New information</param>
        void SetOnlyTagInformation(int ID, IMAIMPFileInfoReadOnly finf);

        /// <summary>
        /// Determines whether track enabled inside player
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Switch state</returns>
        bool GetTrackActivationSwitches(int ID);
        /// <summary>
        /// Switch on/off track inside playlist
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New switch state</param>
        void SetTrackActivationSwitches(int ID, bool Val);

        /// <summary>
        /// Number of tracks inside playlist
        /// </summary>
        int Count { get; }

        //TimeSpan PlaylistDuration { get; }
        //long PlaylistSize { get; }

        /// <summary>
        /// Name of playlist
        /// </summary>
        string PlaylistName { get; }

        /// <summary>
        /// Is this instance work with real player playlist
        /// </summary>
        bool IsConnected { get; }
    }

}
