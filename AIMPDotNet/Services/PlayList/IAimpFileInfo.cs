namespace AIMP.SDK.Services.PlayList
{
    using System;
    using System.Drawing;

    /// <summary>
    /// 
    /// </summary>
    public interface IAimpFileInfo
    {
        /// <summary>
        /// Gets or sets the custom data.
        /// </summary>
        string CustomData { get; set; }

        /// <summary>
        /// Gets or sets the album name.
        /// </summary>
        string Album { get; set; }

        /// <summary>
        /// Gets or sets the album artist.
        /// </summary>
        string AlbumArtist { get; set; }

        /// <summary>
        /// Gets or sets the gain.
        /// </summary>
        double Gain { get; set; }

        /// <summary>
        /// Gets or sets the peak.
        /// </summary>
        double Peak { get; set; }

        /// <summary>
        /// Gets or sets the artist.
        /// </summary>
        string Artist { get; set; }

        /// <summary>
        /// Gets or sets the bit rate.
        /// </summary>
        int BitRate { get; set; }

        /// <summary>
        /// Gets or sets the bit depth.
        /// </summary>
        int BitDepth { get; set; }

        /// <summary>
        /// Gets or sets the BPM.
        /// </summary>
        int BPM { get; set; }

        /// <summary>
        /// Gets or sets the channels.
        /// </summary>
        int Channels { get; set; }

        /// <summary>
        /// Gets or sets the codec.
        /// </summary>
        string Codec { get; set; }

        /// <summary>
        /// Gets or sets the comment.
        /// </summary>
        string Comment { get; set; }

        /// <summary>
        /// Gets or sets the composer.
        /// </summary>
        string Composer { get; set; }

        /// <summary>
        /// Gets or sets the copy right.
        /// </summary>
        string CopyRight { get; set; }
        
        /// <summary>
        /// Gets or sets the cue sheet.
        /// </summary>
        string CUESheet { get; set; }
        
        /// <summary>
        /// Gets or sets the date.
        /// </summary>
        string Date { get; set; }
        
        /// <summary>
        /// Gets or sets the disk number.
        /// </summary>
        string DiskNumber { get; set; }

        /// <summary>
        /// Gets or sets the disk total.
        /// </summary>
        string DiskTotal { get; set; }

        /// <summary>
        /// Gets or sets the duration.
        /// </summary>
        double Duration { get; set; }

        /// <summary>
        /// Gets or sets the name of the file.
        /// </summary>
        string FileName { get; set; }
        
        /// <summary>
        /// Gets or sets the size of the file.
        /// </summary>
        Int64 FileSize { get; set; }

        /// <summary>
        /// Gets or sets the genre.
        /// </summary>
        string Genre { get; set; }

        /// <summary>
        /// Gets or sets the lyrics.
        /// </summary>
        string Lyrics { get; set; }

        /// <summary>
        /// Gets or sets the mark.
        /// </summary>
        double Mark { get; set; }

        /// <summary>
        /// Gets or sets the publisher.
        /// </summary>
        string Publisher { get; set; }
        
        /// <summary>
        /// Gets or sets the sample rate.
        /// </summary>
        int SampleRate { get; set; }
        
        /// <summary>
        /// Gets or sets the title.
        /// </summary>
        string Title { get; set; }

        /// <summary>
        /// Gets or sets the track gain.
        /// </summary>
        double TrackGain { get; set; }

        /// <summary>
        /// Gets or sets the track number.
        /// </summary>
        string TrackNumber { get; set; }

        /// <summary>
        /// Gets or sets the track peak.
        /// </summary>
        double TrackPeak { get; set; }

        /// <summary>
        /// Gets or sets the track total.
        /// </summary>
        string TrackTotal { get; set; }

        /// <summary>
        /// Gets or sets the URL.
        /// </summary>
        string URL { get; set; }
        
        /// <summary>
        /// Gets or sets the added date.
        /// </summary>
        double AddedDate { get; }
        
        /// <summary>
        /// Gets or sets the last played date.
        /// </summary>
        double LastPlayedDate { get; }
        
        /// <summary>
        /// Gets or sets the stat mark.
        /// </summary>
        double StatMark { get; set; }
        
        /// <summary>
        /// Gets or sets the play count.
        /// </summary>
        int PlayCount { get; }
 
        /// <summary>
        /// Gets or sets the state rating.
        /// </summary>
        double StateRating { get; }

        /// <summary>
        /// Copies all properties from source.
        /// </summary>
        void Assign(IAimpFileInfo source);

        /// <summary>
        /// Clones this instance.
        /// </summary>
        IAimpFileInfo Clone();

        // TODO: Add set functionality;
        /// <summary>
        /// 
        /// </summary>
        Bitmap AlbumArt { get; }
    }
}