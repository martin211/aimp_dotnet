//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Playlist.Objects
{
    /// <summary>
    /// The interface describes playlist group that can contains one or more playlist items.
    /// </summary>
    public interface IAimpPlaylistGroup
    {
        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <value>The name.</value>
        string Name { get; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlaylistGroup" /> is expanded.
        /// </summary>
        /// <value><c>true</c> if expanded; otherwise, <c>false</c>.</value>
        bool Expanded { get; set; }

        /// <summary>
        /// Gets the total duration of items in the group, in seconds.
        /// </summary>
        /// <value>The duration.</value>
        double Duration { get; }

        /// <summary>
        /// Gets the index.
        /// </summary>
        /// <value>The index.</value>
        int Index { get; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlaylistGroup" /> is selected.
        /// </summary>
        /// <value><c>true</c> if selected; otherwise, <c>false</c>.</value>
        bool Selected { get; set; }

        /// <summary>
        /// Gets the count.
        /// </summary>
        /// <value>The count.</value>
        int Count { get; }

        /// <summary>
        /// Gets the item.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpPlaylistItem&gt;.</returns>
        AimpActionResult<IAimpPlaylistItem> GetItem(int index);
    }
}
