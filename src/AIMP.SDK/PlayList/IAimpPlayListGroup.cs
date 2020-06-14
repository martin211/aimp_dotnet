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
namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// The interface describes playlist group that can contains one or more playlist items.
    /// </summary>
    public interface IAimpPlaylistGroup
    {
        /// <summary>
        /// Gets the name.
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlaylistGroup"/> is expanded.
        /// </summary>
        bool Expanded { get; set; }

        /// <summary>
        /// Gets the total duration of items in the group, in seconds.
        /// </summary>
        double Duration { get; }

        /// <summary>
        /// Gets the index.
        /// </summary>
        int Index { get; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlaylistGroup"/> is selected.
        /// </summary>
        bool Selected { get; set; }

        /// <summary>
        /// Gets the count.
        /// </summary>
        int Count { get; }

        /// <summary>
        /// Gets the item.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        AimpActionResult<IAimpPlaylistItem> GetItem(int index);
    }
}