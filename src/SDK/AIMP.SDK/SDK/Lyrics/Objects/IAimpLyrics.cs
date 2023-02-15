//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Objects;

namespace AIMP.SDK.Lyrics.Objects
{
    /// <summary>
    /// Enum LyricsType
    /// </summary>
    public enum LyricsType
    {
        /// <summary>
        /// The unknown
        /// </summary>
        Unknown = 0,

        /// <summary>
        /// The unsynced
        /// </summary>
        UnSynced = 1,

        /// <summary>
        /// The synced
        /// </summary>
        Synced = 2
    }

    /// <summary>
    /// Enum LyricsFormat
    /// </summary>
    public enum LyricsFormat
    {
        /// <summary>
        /// The text
        /// </summary>
        Txt = 0,

        /// <summary>
        /// The LRC
        /// </summary>
        Lrc = 1,

        /// <summary>
        /// The SRT
        /// </summary>
        Srt = 2
    }

    /// <summary>
    /// Interface IAimpLyrics
    /// Implements the <see cref="AIMP.SDK.IAimpObject" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpObject" />
    public interface IAimpLyrics : IAimpObject
    {
        /// <summary>
        /// Gets or sets the song text without tags.
        /// </summary>
        /// <value>The text.</value>
        string Text { get; set; }

        /// <summary>
        /// Gets or sets the text author. Optional.
        /// </summary>
        /// <value>The author.</value>
        string Author { get; set; }

        /// <summary>
        /// Get or sets the album. Optional.
        /// </summary>
        /// <value>The album.</value>
        string Album { get; set; }

        /// <summary>
        /// Gets or sets the song title. Optional.
        /// </summary>
        /// <value>The title.</value>
        string Title { get; set; }

        /// <summary>
        /// Gets or sets the creator. Optional.
        /// </summary>
        /// <value>The creator.</value>
        string Creator { get; set; }

        /// <summary>
        /// Gets or sets the application which was used. Optional.
        /// </summary>
        /// <value>The application.</value>
        string Application { get; set; }

        /// <summary>
        /// Gets or sets the application version.
        /// </summary>
        /// <value>The application version.</value>
        string ApplicationVersion { get; set; }

        /// <summary>
        /// Gets or sets the lyrics type.
        /// </summary>
        /// <value>The type.</value>
        LyricsType Type { get; set; }

        /// <summary>
        /// Gets or sets common offset in milliseconds.
        /// </summary>
        /// <value>The offset.</value>
        int Offset { get; set; }

        /// <summary>
        /// Copy values from source.
        /// </summary>
        /// <param name="source">The source lyrics.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Assign(IAimpLyrics source);

        /// <summary>
        /// Creates a copy of current instance.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpLyrics&gt;.</returns>
        AimpActionResult<IAimpLyrics> Clone();

        /// <summary>
        /// Adds time interval.
        /// </summary>
        /// <param name="timeStart">In milliseconds.</param>
        /// <param name="timeFinish">In milliseconds.</param>
        /// <param name="text">The text.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Add(int timeStart, int timeFinish, string text);

        /// <summary>
        /// Deletes the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Finds the specified time.
        /// </summary>
        /// <param name="time">The time.</param>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> Find(int time, int index);

        /// <summary>
        /// Gets the specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="timeStart">The time start.</param>
        /// <param name="timeFinish">The time finish.</param>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> Get(int index, int timeStart, int timeFinish);

        /// <summary>
        /// Gets the count.
        /// </summary>
        /// <returns>AimpActionResult&lt;System.Int32&gt;.</returns>
        AimpActionResult<int> GetCount();

        /// <summary>
        /// Loads lyrics from file.
        /// </summary>
        /// <param name="virtualFileName">Virtual file name.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult LoadFromFile(string virtualFileName);

        /// <summary>
        /// Loads lyrics from stream.
        /// </summary>
        /// <param name="stream">File stream.</param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult LoadFromStream(IAimpStream stream, LyricsFormat format);

        /// <summary>
        /// Loads lyrics from string.
        /// </summary>
        /// <param name="lyrics">String with lyrics.</param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult LoadFromString(string lyrics, LyricsFormat format);

        /// <summary>
        /// Saves lyrics to file.
        /// </summary>
        /// <param name="fileUri">File.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SaveToFile(string fileUri);

        /// <summary>
        /// Saves lyrics to stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SaveToStream(IAimpStream stream, LyricsFormat format);

        /// <summary>
        /// Saves lyrics to string.
        /// </summary>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat" />.</param>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> SaveToString(LyricsFormat format);
    }
}
