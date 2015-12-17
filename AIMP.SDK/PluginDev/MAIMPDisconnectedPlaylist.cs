using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Disconnected playlist. Represents playlist, that works off line
    /// </summary>
    public class MAIMPDisconnectedPlaylist: MarshalByRefObject, IMAIMPPlaylist, IList<MAIMPFileInfo>
    {
        private List<MAIMPFileInfo> inDataList = null;

        /// <summary>
        /// Creates new playlist
        /// </summary>
        public MAIMPDisconnectedPlaylist() 
        {
            inDataList = new List<MAIMPFileInfo>();
            PlaylistName = DateTime.Now.ToString();
        }
        /// <summary>
        /// Creates new playlist with particular name
        /// </summary>
        /// <param name="PlsName">Playlist name</param>
        public MAIMPDisconnectedPlaylist(string PlsName)
        {
            inDataList = new List<MAIMPFileInfo>();
            PlaylistName = PlsName ?? "";
        }
        /// <summary>
        /// Creates new playlist with tracks
        /// </summary>
        /// <param name="col">Tracks</param>
        public MAIMPDisconnectedPlaylist(IEnumerable<MAIMPFileInfo> col)
        {
            inDataList = new List<MAIMPFileInfo>(col);
            PlaylistName = DateTime.Now.ToString();
        }


        // ==================== IMAIMPPlaylist ===================

        /// <summary>
        /// Removes tracks, that match the filtering function
        /// </summary>
        /// <param name="filter">Filtering</param>
        public void RemoveByFilter(Func<IMAIMPFileInfoReadOnly, bool> filter)
        {
            inDataList.RemoveAll(new Predicate<IMAIMPFileInfoReadOnly>(filter));
        }

        /// <summary>
        /// Sort playlist based on ordering function
        /// </summary>
        /// <param name="filter">Ordering function</param>
        public void SortByFilter(Func<IMAIMPFileInfoReadOnly, IMAIMPFileInfoReadOnly, int> filter)
        {
            inDataList.Sort(new Comparison<IMAIMPFileInfoReadOnly>(filter));
        }

        /// <summary>
        /// Perform reordering track in playlist
        /// </summary>
        /// <param name="SortType">Way of reordering</param>
        public void Sort(AIMPPlaylistSortType SortType)
        {
            switch (SortType)
            {
                case AIMPPlaylistSortType.ByArtist:
                    inDataList.Sort((a, b) => string.Compare(a.Artist, b.Artist));
                    break;
                case AIMPPlaylistSortType.ByDuration:
                    inDataList.Sort((a, b) => TimeSpan.Compare(a.Duration, b.Duration));
                    break;
                case AIMPPlaylistSortType.ByFileName:
                    inDataList.Sort((a, b) => string.Compare(a.FileName, b.FileName));
                    break;
                case AIMPPlaylistSortType.ByTitle:
                    inDataList.Sort((a, b) => string.Compare(a.Title, b.Title));
                    break;
                case AIMPPlaylistSortType.Inverse:
                    inDataList.Reverse();
                    break;
                case AIMPPlaylistSortType.Randomize:
                    Random rnd = new Random(DateTime.Now.Millisecond);
                    inDataList.Sort((a, b) => rnd.Next(-1, 1));
                    break;
            }
        }

        /// <summary>
        /// Remove one track from playlist
        /// </summary>
        /// <param name="ID">Position of track</param>
        /// <returns>Success</returns>
        public bool RemoveAt(int ID)
        {
            inDataList.RemoveAt(ID);
            return true;
        }

        /// <summary>
        /// Move track inside playlist
        /// </summary>
        /// <param name="FromId">Current position of track</param>
        /// <param name="ToId">New position</param>
        /// <returns>Success</returns>
        public bool Move(int FromId, int ToId)
        {
            MAIMPFileInfo tmp = inDataList[FromId];
            inDataList.RemoveAt(FromId);
            inDataList.Insert(ToId, tmp);
            return true;
        }

        /// <summary>
        /// Add new file to playlist (information doesn't load automatically)
        /// </summary>
        /// <param name="FileName">Path to file</param>
        /// <returns>Success</returns>
        bool IMAIMPPlaylist.Add(string FileName)
        {
            inDataList.Add(new MAIMPFileInfo() { FileName = FileName });
            return true;
        }

        /// <summary>
        /// Add new track to playlist
        /// </summary>
        /// <param name="finf">Information about track</param>
        /// <returns>Success</returns>
        bool IMAIMPPlaylist.Add(IMAIMPFileInfoReadOnly finf)
        {
            inDataList.Add(new MAIMPFileInfo(finf));
            return true;
        }

        /// <summary>
        /// Add several tracks to playlist (information doesn't load automatically)
        /// </summary>
        /// <param name="Files">Paths to files</param>
        void IMAIMPPlaylist.AddRange(IEnumerable<string> Files)
        {
            foreach (string fname in Files)
                inDataList.Add(new MAIMPFileInfo() { FileName = fname });
        }

        /// <summary>
        /// Add several track to playlist
        /// </summary>
        /// <param name="Files">Inforamtion about tracks</param>
        void IMAIMPPlaylist.AddRange(IEnumerable<IMAIMPFileInfoReadOnly> Files)
        {
            foreach (IMAIMPFileInfoReadOnly fdat in Files)
                inDataList.Add(new MAIMPFileInfo(fdat));
        }

        /// <summary>
        /// Insert file to playlist (information doesn't load automatically)
        /// </summary>
        /// <param name="Pos">Position of new file</param>
        /// <param name="FileName">Path to file</param>
        /// <returns>Success</returns>
        bool IMAIMPPlaylist.Insert(int Pos, string FileName)
        {
            inDataList.Insert(Pos, new MAIMPFileInfo() { FileName = FileName });
            return true;
        }

        /// <summary>
        /// Insert track to playlist
        /// </summary>
        /// <param name="Pos">Position of new track</param>
        /// <param name="finf">Information about track</param>
        /// <returns>Success</returns>
        bool IMAIMPPlaylist.Insert(int Pos, IMAIMPFileInfoReadOnly finf)
        {
            inDataList.Insert(Pos, new MAIMPFileInfo(finf));
            return true;
        }

        /// <summary>
        /// Clear playlist
        /// </summary>
        public void Clear()
        {
            inDataList.Clear();
        }

        /// <summary>
        /// Return title of track inside playlist
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Title</returns>
        public string GetTrackTitle(int ID)
        {
            if (ID < inDataList.Count && ID > 0)
                return inDataList[ID].Title;
            return null;
        }

        /// <summary>
        /// Return path to track file
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Path to file</returns>
        public string GetTrackFileName(int ID)
        {
            if (ID < inDataList.Count && ID > 0)
                return inDataList[ID].FileName;
            return null;
        }

        /// <summary>
        /// Set new path for particular track inside playlist (change only track, not information)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New path</param>
        void IMAIMPPlaylist.SetTrackFileName(int ID, string Val)
        {
            if (ID < inDataList.Count && ID > 0)
                inDataList[ID].FileName = Val;
        }

        /// <summary>
        /// Return information about particular track
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Information about track</returns>
        MAIMPFileInfo IMAIMPPlaylist.GetTrackInformation(int ID)
        {
            return inDataList[ID];
        }

        /// <summary>
        /// Set track information for particular file inside playlist (can change the path to track)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New information</param>
        public void SetTrackInformation(int ID, IMAIMPFileInfoReadOnly Val)
        {
            if (ID < inDataList.Count && ID > 0)
                inDataList[ID].CopyFrom(Val);
        }

        /// <summary>
        /// Set track information except path for particular file inside playlist.
        /// (Change only tags info)
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="finf">New information</param>
        public void SetOnlyTagInformation(int ID, IMAIMPFileInfoReadOnly finf)
        {
            if (ID < inDataList.Count && ID > 0)
            {
                MAIMPFileInfo curF = inDataList[ID];
                curF.Album = finf.Album;
                curF.Artist = finf.Artist;
                curF.Date = finf.Date;
                curF.Genre = finf.Genre;
                curF.Rating = finf.Rating;
                curF.Title = finf.Title;
                curF.TrackID = finf.TrackID;
            }
        }

        /// <summary>
        /// Determines whether track enabled
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <returns>Switch state</returns>
        public bool GetTrackActivationSwitches(int ID)
        {
            if (ID < inDataList.Count && ID > 0)
                return inDataList[ID].IsActive;
            return false;
        }

        /// <summary>
        /// Switch on/off track inside playlist
        /// </summary>
        /// <param name="ID">Poition of track inside playlist</param>
        /// <param name="Val">New switch state</param>
        public void SetTrackActivationSwitches(int ID, bool Val)
        {
            inDataList[ID].IsActive = Val;
        }

        /// <summary>
        /// Number of tracks inside playlist
        /// </summary>
        public int Count
        {
            get { return inDataList.Count; }
        }

        /// <summary>
        /// Gets or sets name of playlist
        /// </summary>
        public string PlaylistName
        {
            get; set;
        }

        /// <summary>
        /// Is this instance work with real player playlist
        /// </summary>
        bool IMAIMPPlaylist.IsConnected
        {
            get { return false; }
        }
   
        // ==================== IList<MAIMPFileInfo> ===============

        /// <summary>
        /// Returns index of track inside playlist
        /// </summary>
        /// <param name="item">Track</param>
        /// <returns>Index</returns>
        public int IndexOf(MAIMPFileInfo item)
        {
            return inDataList.IndexOf(item);
        }

        /// <summary>
        /// Insert track to playlist
        /// </summary>
        /// <param name="index">Position</param>
        /// <param name="item">Track information</param>
        public void Insert(int index, MAIMPFileInfo item)
        {
            inDataList.Insert(index, item);
        }

        void IList<MAIMPFileInfo>.RemoveAt(int index)
        {
            inDataList.RemoveAt(index);
        }

        /// <summary>
        /// Gets or sets track information inside playlist
        /// </summary>
        /// <param name="index">Position of track</param>
        /// <returns>Track information</returns>
        public MAIMPFileInfo this[int index]
        {
            get
            {
                return inDataList[index];
            }
            set
            {
                inDataList[index] = value;
            }
        }

        /// <summary>
        /// Add track information to playlist
        /// </summary>
        /// <param name="item">Track inforamtion</param>
        public void Add(MAIMPFileInfo item)
        {
            inDataList.Add(item);
        }

        /// <summary>
        /// Detemine, if playlist contains track
        /// </summary>
        /// <param name="item">Track</param>
        /// <returns>Is contains</returns>
        public bool Contains(MAIMPFileInfo item)
        {
            return inDataList.Contains(item);
        }

        /// <summary>
        /// Copy playlist to array
        /// </summary>
        /// <param name="array">Array</param>
        /// <param name="arrayIndex">Start index inside array</param>
        public void CopyTo(MAIMPFileInfo[] array, int arrayIndex)
        {
            inDataList.CopyTo(array, arrayIndex);
        }

        bool ICollection<MAIMPFileInfo>.IsReadOnly
        {
            get { throw new NotImplementedException(); }
        }

        /// <summary>
        /// Removes track from playlist
        /// </summary>
        /// <param name="item">Track</param>
        /// <returns>Success</returns>
        public bool Remove(MAIMPFileInfo item)
        {
            return inDataList.Remove(item);
        }

        /// <summary>
        /// Returns enumerator for playlist
        /// </summary>
        /// <returns>Enumerator</returns>
        public IEnumerator<MAIMPFileInfo> GetEnumerator()
        {
            return inDataList.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        // ==========================

        /// <summary>
        /// Add several tracks to playlist
        /// </summary>
        /// <param name="Files">Track information</param>
        void AddRange(IEnumerable<MAIMPFileInfo> Files)
        {
            inDataList.AddRange(Files);
        }

    }
}
