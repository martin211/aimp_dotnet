//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Drawing;

namespace AIMP.SDK.FileManager.Objects
{
    /// <summary>
    /// Storage for extended information about the file.
    /// Implements the <see cref="AIMP.SDK.IAimpObject" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpObject" />
    public interface IAimpFileInfo : IAimpObject
    {
        /// <summary>
        /// Gets or sets the custom data.
        /// <para>
        /// It allow to bind custom data to the interface.
        /// </para>
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
        /// Gets or sets the album gain.
        /// </summary>
        double AlbumGain { get; set; }

        /// <summary>
        /// Gets or sets the album peak.
        /// </summary>
        double AlbumPeak { get; set; }

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
        long FileSize { get; set; }

        /// <summary>
        /// Gets or sets the genre.
        /// </summary>
        string Genre { get; set; }

        /// <summary>
        /// Gets or sets the lyrics.
        /// </summary>
        string Lyrics { get; set; }

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
        /// Gets or sets the conductor.
        /// </summary>
        string Conductor { get; set; }

        /// <summary>
        /// Gets or sets the mood.
        /// </summary>
        string Mood { get; set; }

        /// <summary>
        /// Gets or sets the catalog.
        /// </summary>
        string Catalog { get; set; }

        /// <summary>
        /// Gets or sets the isrc.
        /// </summary>
        string Isrc { get; set; }

        /// <summary>
        /// Gets or sets the lyricist.
        /// </summary>
        string Lyricist { get; set; }

        /// <summary>
        /// Gets or sets the encoded by.
        /// </summary>
        string EncodedBy { get; set; }

        /// <summary>
        /// Gets or sets the Rating of the track that stored in tags of file. Can be in range from 0 to 5.
        /// </summary>
        int Rating { get; set; }

        /// <summary>
        /// Gets the adding date to DB of Audio Library
        /// </summary>
        DateTime StatAddingDate { get; }

        /// <summary>
        /// Gets the date of last playback.
        /// </summary>
        DateTime StatLastPlayDate { get; }

        /// <summary>
        /// Gets or sets the user mark that stored in DB of Audio Library (0..5).
        /// </summary>
        double StatMark { get; set; }

        /// <summary>
        /// Gets the playback count.
        /// </summary>
        int StatPlayCount { get; }

        /// <summary>
        /// Gets the rating for track, that calculates automatically based on all the statistics from the DB (0 to 1). 
        /// </summary>
        /// <value>The state rating.</value>
        double StatRating { get; }


        /// <summary>
        /// Gets or sets the mark that displayed for user (0..5).
        /// Mark can be equal to rating value (depended from settings of Audio Library).
        /// </summary>
        /// <value>The stat displaying rating.</value>
        double StatDisplayingMark { get; set; }

        /// <summary>
        /// Gets or sets the album art.
        /// </summary>
        /// <value>The album art.</value>
        Bitmap AlbumArt { get; set; }

        /// <summary>
        /// Copies all properties from source.
        /// </summary>
        /// <param name="source">The source.</param>
        void Assign(IAimpFileInfo source);

        /// <summary>
        /// Clones this instance.
        /// </summary>
        /// <returns>IAimpFileInfo.</returns>
        IAimpFileInfo Clone();
    }
}
