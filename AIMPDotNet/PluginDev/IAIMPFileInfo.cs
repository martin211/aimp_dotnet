using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    /// <summary>
    /// Information about audio track only for read
    /// </summary>
	public interface IMAIMPFileInfoReadOnly
	{
        /// <summary>
        /// Is track enabled in player
        /// </summary>
		Boolean IsActive { get; }
        /// <summary>
        /// Track BitRate
        /// </summary>
		UInt32 BitRate { get; }
        /// <summary>
        /// Number of audio channels
        /// </summary>
		UInt32 ChanelNumber { get; }
        /// <summary>
        /// Track duration
        /// </summary>
		TimeSpan Duration { get; }
        /// <summary>
        /// Size of track file
        /// </summary>
		UInt64 FileSize { get; }
        /// <summary>
        /// Rating (from tags)
        /// </summary>
		UInt32 Rating { get; }
        /// <summary>
        /// Track sample rate
        /// </summary>
		UInt32 SampleRate { get; }
        /// <summary>
        /// Track ID (from tags)
        /// </summary>
		UInt32 TrackID { get; }

        /// <summary>
        /// Album name (from tags)
        /// </summary>
		String Album { get; }
        /// <summary>
        /// Artist (from tags)
        /// </summary>
		String Artist { get; }
        /// <summary>
        /// Track release date (from tags)
        /// </summary>
		String Date { get; }
        /// <summary>
        /// Path to the track file
        /// </summary>
		String FileName { get; }
        /// <summary>
        /// Genre (from tags)
        /// </summary>
		String Genre { get; }
        /// <summary>
        /// Track title (from tags)
        /// </summary>
		String Title { get; }
	}

    /// <summary>
    /// Inforamtion about audio track
    /// </summary>
	public interface IMAIMP2FileInfo: IMAIMPFileInfoReadOnly
	{
        /// <summary>
        /// Is track enabled in player
        /// </summary>
        new Boolean IsActive { get; set; }
        /// <summary>
        /// Track BitRate
        /// </summary>
		new UInt32 BitRate { get; set; }
        /// <summary>
        /// Number of audio channels
        /// </summary>
        new UInt32 ChanelNumber { get; set; }
        /// <summary>
        /// Track duration
        /// </summary>
        new TimeSpan Duration { get; set; }
        /// <summary>
        /// Size of track file
        /// </summary>
        new UInt64 FileSize { get; set; }
        /// <summary>
        /// Rating (from tags)
        /// </summary>
        new UInt32 Rating { get; set; }
        /// <summary>
        /// Track sample rate
        /// </summary>
        new UInt32 SampleRate { get; set; }
        /// <summary>
        /// Track ID (from tags)
        /// </summary>
        new UInt32 TrackID { get; set; }

        /// <summary>
        /// Album name (from tags)
        /// </summary>
        new String Album { get; set; }
        /// <summary>
        /// Artist (from tags)
        /// </summary>
        new String Artist { get; set; }
        /// <summary>
        /// Track release date (from tags)
        /// </summary>
        new String Date { get; set; }
        /// <summary>
        /// Path to the track file
        /// </summary>
        new String FileName { get; set; }
        /// <summary>
        /// Genre (from tags)
        /// </summary>
        new String Genre { get; set; }
        /// <summary>
        /// Track title (from tags)
        /// </summary>
        new String Title { get; set; }
	};


    /// <summary>
    /// Inforamtion about audio track
    /// </summary>
    [Serializable]
    public class MAIMPFileInfo : IMAIMP2FileInfo
	{
		public MAIMPFileInfo() 
        {
            Album = string.Empty;
            Artist = string.Empty;
            Date =   string.Empty;
            Genre =  string.Empty;
            Title =  string.Empty;
            FileName = string.Empty;
        }
        /// <summary>
        /// Copy constructor
        /// </summary>
        /// <param name="Dat">Source information</param>
		public MAIMPFileInfo(IMAIMPFileInfoReadOnly Dat)
		{
			IsActive = Dat.IsActive;
			BitRate = Dat.BitRate;
			ChanelNumber = Dat.ChanelNumber;
			Duration = Dat.Duration;
			FileSize = Dat.FileSize;
			Rating = Dat.Rating;
			SampleRate = Dat.SampleRate;
			TrackID = Dat.TrackID;
			Album = Dat.Album;
			Artist = Dat.Artist;
			Date = Dat.Date;
			Genre = Dat.Genre;
			Title = Dat.Title;
			FileName = Dat.FileName;
		}
        /// <summary>
        /// Copy all data from another object
        /// </summary>
        /// <param name="Dat">Source information</param>
        public void CopyFrom(IMAIMPFileInfoReadOnly Dat)
        {
            IsActive = Dat.IsActive;
            BitRate = Dat.BitRate;
            ChanelNumber = Dat.ChanelNumber;
            Duration = Dat.Duration;
            FileSize = Dat.FileSize;
            Rating = Dat.Rating;
            SampleRate = Dat.SampleRate;
            TrackID = Dat.TrackID;
            Album = Dat.Album;
            Artist = Dat.Artist;
            Date = Dat.Date;
            Genre = Dat.Genre;
            Title = Dat.Title;
            FileName = Dat.FileName;
        }


        /// <summary>
        /// Is track enabled in player
        /// </summary>
		public Boolean IsActive { get; set; }
        /// <summary>
        /// Track BitRate
        /// </summary>
		public UInt32 BitRate { get; set; }
        /// <summary>
        /// Number of audio channels
        /// </summary>
		public UInt32 ChanelNumber { get; set; }
        /// <summary>
        /// Track duration
        /// </summary>
		public TimeSpan Duration { get; set; }
        /// <summary>
        /// Size of track file
        /// </summary>
        public UInt64 FileSize { get; set; }
        /// <summary>
        /// Rating (from tags)
        /// </summary>
        public UInt32 Rating { get; set; }
        /// <summary>
        /// Track sample rate
        /// </summary>
        public UInt32 SampleRate { get; set; }
        /// <summary>
        /// Track ID (from tags)
        /// </summary>
        public UInt32 TrackID { get; set; }

        /// <summary>
        /// Album name (from tags)
        /// </summary>
        public String Album { get; set; }
        /// <summary>
        /// Artist (from tags)
        /// </summary>
        public String Artist { get; set; }
        /// <summary>
        /// Track release date (from tags)
        /// </summary>
        public String Date { get; set; }
        /// <summary>
        /// Path to the track file
        /// </summary>
        public String FileName { get; set; }
        /// <summary>
        /// Genre (from tags)
        /// </summary>
        public String Genre { get; set; }
        /// <summary>
        /// Track title (from tags)
        /// </summary>
        public String Title { get; set; }


        public override string ToString()
        {
            return (Artist??"") + " - " + (Title??"");
        }
	};
}
