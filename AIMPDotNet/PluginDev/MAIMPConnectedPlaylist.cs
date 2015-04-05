using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Connected playlist. Represent playlist inside player.
    /// </summary>
	public abstract class MAIMPConnectedPlaylist: MarshalByRefObject, IMAIMPPlaylist
	{
		// ============= IMAIMPPlaylist =================

        /// <summary>
        /// Removes tracks, that match the filtering function
        /// </summary>
        /// <param name="filter">Filtering</param>
		public abstract void RemoveByFilter(System.Func<IMAIMPFileInfoReadOnly, Boolean> filter);
        /// <summary>
        /// Sort playlist based on ordering function
        /// </summary>
        /// <param name="filter">Ordering function</param>
        public abstract void SortByFilter(System.Func<IMAIMPFileInfoReadOnly, IMAIMPFileInfoReadOnly, Int32> filter);
        /// <summary>
        /// Perform reordering track in playlist
        /// </summary>
        /// <param name="SortType">Way of reordering</param>
        public abstract void Sort(AIMPPlaylistSortType SortType);
        /// <summary>
        /// Remove one track from playlist
        /// </summary>
        /// <param name="ID">Position of track</param>
        /// <returns>Success</returns>
        public abstract Boolean RemoveAt(Int32 ID);
        /// <summary>
        /// Move track inside playlist
        /// </summary>
        /// <param name="FromId">Current position of track</param>
        /// <param name="ToId">New position</param>
        /// <returns>Success</returns>
        public abstract Boolean Move(Int32 FromId, Int32 ToId);
        /// <summary>
        /// Add new file to playlist (information from tags doesn't load automatically)
        /// </summary>
        /// <param name="FileName">Path to file</param>
        /// <returns>Success</returns>
        public abstract Boolean Add(String FileName);
        /// <summary>
        /// Add new track to playlist
        /// </summary>
        /// <param name="finf">Information about track</param>
        /// <returns>Success</returns>
        public abstract Boolean Add(IMAIMPFileInfoReadOnly finf);
        /// <summary>
        /// Add several tracks to playlist (information from tags doesn't load automatically)
        /// </summary>
        /// <param name="Files">Path to files</param>
        public abstract void AddRange(System.Collections.Generic.IEnumerable<String> Files);
        /// <summary>
        /// Add several track to playlist
        /// </summary>
        /// <param name="Files">Inforamtion about tracks</param>
        public abstract void AddRange(System.Collections.Generic.IEnumerable<IMAIMPFileInfoReadOnly> Files);
        /// <summary>
        /// Insert file to playlist (information from tags doesn't load automatically)
        /// </summary>
        /// <param name="Pos">Position of new file</param>
        /// <param name="FileName">Path to file</param>
        /// <returns>Success</returns>
        public abstract Boolean Insert(Int32 Pos, String FileName);
        /// <summary>
        /// Insert track to playlist
        /// </summary>
        /// <param name="Pos">Position of new track</param>
        /// <param name="finf">Information about track</param>
        /// <returns>Success</returns>
        public abstract Boolean Insert(Int32 Pos, IMAIMPFileInfoReadOnly finf);
        /// <summary>
        /// Clear playlist
        /// </summary>
        public abstract void Clear();
        /// <summary>
        /// Return title of track inside playlist
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Title</returns>
        public abstract String GetTrackTitle(Int32 ID);
        /// <summary>
        /// Return path to track file
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Path to file</returns>
        public abstract String GetTrackFileName(Int32 ID);
        /// <summary>
        /// Set new path for particular track inside playlist (change only track, not information)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New path</param>
        public abstract void SetTrackFileName(Int32 ID, String Val);
        /// <summary>
        /// Return information about particular track
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Information about track</returns>
        public abstract MAIMPFileInfo GetTrackInformation(Int32 ID);
        /// <summary>
        /// Set track information for particular file inside playlist (can change the path to track)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New information</param>
        public abstract void SetTrackInformation(Int32 ID, IMAIMPFileInfoReadOnly Val);
        /// <summary>
        /// Set track information except path for particular file inside playlist.
        /// (Change only tags info)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="finf">New information</param>
        public abstract void SetOnlyTagInformation(Int32 ID, IMAIMPFileInfoReadOnly finf);
        /// <summary>
        /// Determines whether track enabled inside player
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Switch state</returns>
        public abstract Boolean GetTrackActivationSwitches(Int32 ID);
        /// <summary>
        /// Switch on/off track inside playlist
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New switch state</param>
        public abstract void SetTrackActivationSwitches(Int32 ID, Boolean Val);

        /// <summary>
        /// Number of tracks inside playlist
        /// </summary>
        public abstract Int32 Count { get; }
        /// <summary>
        /// Name of playlist
        /// </summary>
        public abstract String PlaylistName { get; }
        Boolean IMAIMPPlaylist.IsConnected { get { return true; } }
        //=============================

        /// <summary>
        /// Gets or sets selected track ID
        /// </summary>
		public abstract Int32 SelectedTrack { get; set; }
        /// <summary>
        /// Reload information for particular track inside playlist
        /// </summary>
        /// <param name="ID">Position of track</param>
        /// <returns>Success</returns>
		public abstract Boolean ReloadTrackInfo(Int32 ID);
        /// <summary>
        /// Reload track information for whole playlist
        /// </summary>
		public abstract void ReloadFullPlaylistInfo();
        /// <summary>
        /// Save playlist to file
        /// </summary>
        /// <param name="FileName">Path to file</param>
		public abstract void SavePlaylist(String FileName);
        /// <summary>
        /// Add tracks to playlist from playlist file
        /// </summary>
        /// <param name="FileName">Path to playlist file</param>
		public abstract void LoadTracksFromPlaylist(String FileName);
        /// <summary>
        /// Sort tracks by template string
        /// </summary>
        /// <param name="TemplateStr">Template string</param>
		public abstract void SortByTemplate(String TemplateStr);
        /// <summary>
        /// Add new track to playlist
        /// </summary>
        /// <param name="FileName">Path to file</param>
        /// <param name="AutoLoadInfo">If true, loads information from tags</param>
        /// <returns>Success</returns>
		public abstract Boolean Add(String FileName, Boolean AutoLoadInfo);
        /// <summary>
        /// Add several tracks to playlist
        /// </summary>
        /// <param name="Files">Path to audio files</param>
        /// <param name="AutoLoadInfo">If true, loads information from tags</param>
		public abstract void AddRange(System.Collections.Generic.IEnumerable<String> Files, Boolean AutoLoadInfo);
		/// <summary>
		/// Insert track to playlist
		/// </summary>
		/// <param name="Pos">Position</param>
		/// <param name="FileName">Path to file</param>
        /// <param name="AutoLoadInfo">If true, loads information from tags</param>
		/// <returns>Success</returns>
        public abstract Boolean Insert(Int32 Pos, String FileName, Boolean AutoLoadInfo);
		/// <summary>
		/// Change one track to another inside playlist
		/// </summary>
		/// <param name="ID">Position of track inside playlist</param>
		/// <param name="FileName">Path to new audio file</param>
        /// <param name="AutoLoadInfo">If true, loads information from tags</param>
		/// <returns>Success</returns>
        public abstract Boolean SetTrackFileName(Int32 ID, String FileName, Boolean AutoLoadInfo);
		/// <summary>
		/// Position of currently playing track
		/// </summary>
        public abstract Int32 PlayingTrackIndex { get; set; }
        /// <summary>
        /// Plays track inside playlist
        /// </summary>
        /// <param name="ID">Track position</param>
        /// <returns>Success</returns>
		public abstract Boolean PlayTrack(Int32 ID);
        /// <summary>
        /// Is this playlist active
        /// </summary>
		public abstract Boolean IsPlaylistActive { get; }
        /// <summary>
        /// If this playlist now playing
        /// </summary>
		public abstract Boolean IsPlaylistPlaying { get; }


        /// <summary>
        /// Duration of playlist
        /// </summary>
		public abstract TimeSpan PlaylistDuration { get; }
        /// <summary>
        /// Total audio files size in bytes
        /// </summary>
		public abstract Int64 PlaylistSize { get; }


    	internal abstract Int32 PlaylistID { get; }

		public static Boolean operator==(MAIMPConnectedPlaylist a, MAIMPConnectedPlaylist b)
		{
            if (((object)a) != null && ((object)b) != null)
                return a.PlaylistID == b.PlaylistID;
            return (object)a == (object)b;
		}
		public static Boolean operator!=(MAIMPConnectedPlaylist a, MAIMPConnectedPlaylist b)
		{
            if (((object)a) != null && ((object)b) != null)
			    return a.PlaylistID != b.PlaylistID;
            return (object)a != (object)b;
		}

        public override string ToString()
        {
            return PlaylistName;
        }

        public override bool Equals(object obj)
        {
            if (obj != null && obj is MAIMPConnectedPlaylist)
                return PlaylistID == (obj as MAIMPConnectedPlaylist).PlaylistID;
            return base.Equals(obj);
        }
        public override int GetHashCode()
        {
            return PlaylistID.GetHashCode();
        }
    };
}
