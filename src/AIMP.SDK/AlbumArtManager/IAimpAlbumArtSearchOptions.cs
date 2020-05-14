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
namespace AIMP.SDK.AlbumArtManager
{
    /// <summary>
    /// The search options for album art.
    /// </summary>
    public interface IAimpAlbumArtSearchOptions
    {
        /// <summary>
        /// Gets or sets a value indicating whether allow an ability to find album art in files.
        /// </summary>
        bool FindInFiles { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether allow an ability to find album art in internet.
        /// </summary>
        bool FindInInternet { get; set; }

        /// <summary>
        /// Gets or sets the file masks for searching.
        /// <para>
        /// List of templates (without extensions) for searching.
        /// Each value must be separated from others via ";".
        /// </para>
        /// </summary>
        string[] FileMasks { get; set; }

        /// <summary>
        /// Gets or sets the available cover file extensions.
        /// <para>
        /// List of extensions that are supported. 
        /// Each value must be separated from others via ";".
        /// </para>
        /// </summary>
        string[] FileExtensions { get; set; }

        /// <summary>
        /// Gets or sets the maximum size of the file which can be downloaded from internet.
        /// 0 - size is unlimited.
        /// </summary>
        int MaxFileSize { get; set; }
    }
}