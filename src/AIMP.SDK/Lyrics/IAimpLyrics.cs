// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.Lyrics
{
    public enum LyricsType
    {
        Unknown = 0,
        Unsynced = 1,
        Synced = 2
    }

    public enum LyricsFormat
    {
        Txt = 0,
        Lrc = 1,
        Srt = 2
    }

    public interface IAimpLyrics
    {
        /// <summary>
        /// Gets or sets the song text without tags.
        /// </summary>
        string Text { get; set; }

        /// <summary>
        /// Gets or sets the text author. Optional.
        /// </summary>
        string Author { get; set; }

        /// <summary>
        /// Get or sets the album. Optional.
        /// </summary>
        string Album { get; set; }

        /// <summary>
        /// Gets or sets the song title. Optional.
        /// </summary>
        string Title { get; set; }

        /// <summary>
        /// Gets or sets the creator. Optional.
        /// </summary>
        string Creator { get; set; }

        /// <summary>
        /// Gets or sets the application which was used. Optional.
        /// </summary>
        string Application { get; set; }

        /// <summary>
        /// Gets or sets the application version.
        /// </summary>
        string ApplicationVersion { get; set; }

        /// <summary>
        /// Gets or sets the lyrics type.
        /// </summary>
        LyricsType Type { get; set; }

        /// <summary>
        /// Gets or sets common offset in milliseconds.
        /// </summary>
        int Offset { get; set; }

        /// <summary>
        /// Copy values from source.
        /// </summary>
        /// <param name="source">The source lyrics.</param>
        AimpActionResult Assign(IAimpLyrics source);

        /// <summary>
        /// Creates a copy of current instance.
        /// </summary>
        /// <param name="lyrics"></param>
        AimpActionResult Clone(out IAimpLyrics lyrics);

        /// <summary>
        /// Adds time interval.
        /// </summary>
        /// <param name="timeStart">In milliseconds.</param>
        /// <param name="timeFinish">In milliseconds.</param>
        /// <param name="text"></param>
        AimpActionResult Add(int timeStart, int timeFinish, string text);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="time"></param>
        /// <param name="index"></param>
        /// <param name="text"></param>
        /// <returns></returns>
        AimpActionResult<string> Find(int time, int index);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="index"></param>
        /// <param name="timeStart"></param>
        /// <param name="timeFinish"></param>
        /// <param name="text"></param>
        /// <returns></returns>
        AimpActionResult<string> Get(int index, int timeStart, int timeFinish);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        AimpActionResult<int> GetCount(ref int value);

        /// <summary>
        /// Loads lyrics from file.
        /// </summary>
        /// <param name="virtualFileName">Virtual file name.</param>
        /// <returns></returns>
        AimpActionResult LoadFromFile(string virtualFileName);

        /// <summary>
        /// Loads lyrics from stream.
        /// </summary>
        /// <param name="stream">File stream.</param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat"/>.</param>
        /// <returns></returns>
        AimpActionResult LoadFromStream(IAimpStream stream, LyricsFormat format);

        /// <summary>
        /// Loads lyrics from string.
        /// </summary>
        /// <param name="lyrics">String with lyrics.</param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat"/>.</param>
        /// <returns></returns>
        AimpActionResult LoadFromString(string lyrics, LyricsFormat format);

        /// <summary>
        /// Saves lyrics to file.
        /// </summary>
        /// <param name="fileUri">File.</param>
        /// <returns></returns>
        AimpActionResult SaveToFile(string fileUri);

        /// <summary>
        /// Saves lyrics to stream.
        /// </summary>
        /// <param name="stream"></param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat"/>.</param>
        /// <returns></returns>
        AimpActionResult SaveToStream(IAimpStream stream, LyricsFormat format);

        /// <summary>
        /// Saves lyrics to string.
        /// </summary>
        /// <param name="lyrics"></param>
        /// <param name="format">Lyrics format <seealso cref="LyricsFormat"/>.</param>
        /// <returns></returns>
        AimpActionResult SaveToString(out string lyrics, LyricsFormat format);
    }
}