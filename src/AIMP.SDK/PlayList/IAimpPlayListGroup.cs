namespace AIMP.SDK.PlayList
{
    /// <summary>
    /// The interface describes playlist group that can contains one or more playlist items.
    /// </summary>
    public interface IAimpPlayListGroup
    {
        /// <summary>
        /// Gets the name.
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlayListGroup"/> is expanded.
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
        /// Gets or sets a value indicating whether this <see cref="IAimpPlayListGroup"/> is selected.
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
        IAimpPlaylistItem GetItem(int index);
    }
}