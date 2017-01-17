namespace AIMP.SDK.AlbumArtManager
{
    public interface IAimpAlbumArtSearchOptions
    {
        /// <summary>
        /// Gets or sets a value indicating whether [find in files].
        /// </summary>
        bool FindInFiles { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [find in internet].
        /// </summary>
        bool FindInInternet { get; set; }

        /// <summary>
        /// Gets or sets the file masks.
        /// </summary>
        string[] FileMasks { get; set; }

        /// <summary>
        /// Gets or sets the availabel cover file extensions.
        /// </summary>
        string[] FileExtensions { get; set; }

        /// <summary>
        /// Gets or sets the maximum size of the file wich can be downloaded from internet.
        /// </summary>
        int MaxFileSize { get; set; }
    }
}