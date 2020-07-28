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

using System;
using System.Drawing;

namespace AIMP.SDK.FileManager
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
        /// <value>The custom data.</value>
        string CustomData { get; set; }

        /// <summary>
        /// Gets or sets the album name.
        /// </summary>
        /// <value>The album.</value>
        string Album { get; set; }

        /// <summary>
        /// Gets or sets the album artist.
        /// </summary>
        /// <value>The album artist.</value>
        string AlbumArtist { get; set; }

        /// <summary>
        /// Gets or sets the gain.
        /// </summary>
        /// <value>The gain.</value>
        double Gain { get; set; }

        /// <summary>
        /// Gets or sets the peak.
        /// </summary>
        /// <value>The peak.</value>
        double Peak { get; set; }

        /// <summary>
        /// Gets or sets the artist.
        /// </summary>
        /// <value>The artist.</value>
        string Artist { get; set; }

        /// <summary>
        /// Gets or sets the bit rate.
        /// </summary>
        /// <value>The bit rate.</value>
        int BitRate { get; set; }

        /// <summary>
        /// Gets or sets the bit depth.
        /// </summary>
        /// <value>The bit depth.</value>
        int BitDepth { get; set; }

        /// <summary>
        /// Gets or sets the BPM.
        /// </summary>
        /// <value>The BPM.</value>
        int BPM { get; set; }

        /// <summary>
        /// Gets or sets the channels.
        /// </summary>
        /// <value>The channels.</value>
        int Channels { get; set; }

        /// <summary>
        /// Gets or sets the codec.
        /// </summary>
        /// <value>The codec.</value>
        string Codec { get; set; }

        /// <summary>
        /// Gets or sets the comment.
        /// </summary>
        /// <value>The comment.</value>
        string Comment { get; set; }

        /// <summary>
        /// Gets or sets the composer.
        /// </summary>
        /// <value>The composer.</value>
        string Composer { get; set; }

        /// <summary>
        /// Gets or sets the copy right.
        /// </summary>
        /// <value>The copy right.</value>
        string CopyRight { get; set; }

        /// <summary>
        /// Gets or sets the cue sheet.
        /// </summary>
        /// <value>The cue sheet.</value>
        string CUESheet { get; set; }

        /// <summary>
        /// Gets or sets the date.
        /// </summary>
        /// <value>The date.</value>
        string Date { get; set; }

        /// <summary>
        /// Gets or sets the disk number.
        /// </summary>
        /// <value>The disk number.</value>
        string DiskNumber { get; set; }

        /// <summary>
        /// Gets or sets the disk total.
        /// </summary>
        /// <value>The disk total.</value>
        string DiskTotal { get; set; }

        /// <summary>
        /// Gets or sets the duration.
        /// </summary>
        /// <value>The duration.</value>
        double Duration { get; set; }

        /// <summary>
        /// Gets or sets the name of the file.
        /// </summary>
        /// <value>The name of the file.</value>
        string FileName { get; set; }

        /// <summary>
        /// Gets or sets the size of the file.
        /// </summary>
        /// <value>The size of the file.</value>
        Int64 FileSize { get; set; }

        /// <summary>
        /// Gets or sets the genre.
        /// </summary>
        /// <value>The genre.</value>
        string Genre { get; set; }

        /// <summary>
        /// Gets or sets the lyrics.
        /// </summary>
        /// <value>The lyrics.</value>
        string Lyrics { get; set; }

        /// <summary>
        /// Gets or sets the mark.
        /// </summary>
        /// <value>The mark.</value>
        double Mark { get; set; }

        /// <summary>
        /// Gets or sets the publisher.
        /// </summary>
        /// <value>The publisher.</value>
        string Publisher { get; set; }

        /// <summary>
        /// Gets or sets the sample rate.
        /// </summary>
        /// <value>The sample rate.</value>
        int SampleRate { get; set; }

        /// <summary>
        /// Gets or sets the title.
        /// </summary>
        /// <value>The title.</value>
        string Title { get; set; }

        /// <summary>
        /// Gets or sets the track gain.
        /// </summary>
        /// <value>The track gain.</value>
        double TrackGain { get; set; }

        /// <summary>
        /// Gets or sets the track number.
        /// </summary>
        /// <value>The track number.</value>
        string TrackNumber { get; set; }

        /// <summary>
        /// Gets or sets the track peak.
        /// </summary>
        /// <value>The track peak.</value>
        double TrackPeak { get; set; }

        /// <summary>
        /// Gets or sets the track total.
        /// </summary>
        /// <value>The track total.</value>
        string TrackTotal { get; set; }

        /// <summary>
        /// Gets or sets the URL.
        /// </summary>
        /// <value>The URL.</value>
        string URL { get; set; }

        /// <summary>
        /// Gets or sets the added date.
        /// </summary>
        /// <value>The added date.</value>
        double AddedDate { get; }

        /// <summary>
        /// Gets or sets the last played date.
        /// </summary>
        /// <value>The last played date.</value>
        double LastPlayedDate { get; }

        /// <summary>
        /// Gets or sets the stat mark.
        /// </summary>
        /// <value>The stat mark.</value>
        double StatMark { get; set; }

        /// <summary>
        /// Gets or sets the play count.
        /// </summary>
        /// <value>The play count.</value>
        int PlayCount { get; }

        /// <summary>
        /// Gets or sets the state rating.
        /// </summary>
        /// <value>The state rating.</value>
        double StateRating { get; }

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