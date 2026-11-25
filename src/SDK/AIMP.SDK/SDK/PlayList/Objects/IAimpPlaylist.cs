using System;
using System.Collections.Generic;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Playlist interface.
/// Implements the <see cref="IAimpPlaylistListener" />
/// </summary>
/// <seealso cref="IAimpPlaylistListener" />
public interface IAimpPlaylist : IAimpPlaylistListener, IDisposable
{
    /// <summary>
    /// Gets the playlist identifier.
    /// </summary>
    /// <value>The identifier.</value>
    string Id { get; }

    /// <summary>
    /// Gets or sets the playlist name.
    /// </summary>
    /// <value>The name.</value>
    string Name { get; set; }

    /// <summary>
    /// Gets the playlist custom properties (AIMP 6.0+).
    /// </summary>
    AimpActionResult<IAimpPlaylistProperties> GetProperties();

    /// <summary>
    /// Gets or sets a value indicating playlist is read only..
    /// </summary>
    /// <value><c>true</c> if [read only]; otherwise, <c>false</c>.</value>
    bool ReadOnly { get; set; }

    /// <summary>
    /// Gets or sets the focused object.
    /// Object should be <see cref="IAimpPlaylistItem" /> or <see cref="IAimpPlaylistGroup" />.
    /// </summary>
    /// <value>The focused item.</value>
    IAimpPlaylistItem FocusedItem { get; set; }

    /// <summary>
    /// Gets or sets the focused group.
    /// </summary>
    /// <value>The focused group.</value>
    IAimpPlaylistGroup FocusedGroup { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [grouping overridden].
    /// </summary>
    /// <value><c>true</c> if [grouping overridden]; otherwise, <c>false</c>.</value>
    bool GroupingOverridden { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether this <see cref="IAimpPlaylist" /> is grouping.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if grouping; otherwise, <c>false</c>.</value>
    bool Grouping { get; set; }

    /// <summary>
    /// Gets or sets the grouping template.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value>The grouping template.</value>
    string GroupingTemplate { get; set; }

    /// <summary>
    /// Enables the auto merge for grouping.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [grouping automerg]; otherwise, <c>false</c>.</value>
    bool GroupingAutomerg { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [formating override].
    /// </summary>
    /// <value><c>true</c> if [formatting override]; otherwise, <c>false</c>.</value>
    bool FormattingOverride { get; set; }

    /// <summary>
    /// Gets or sets the formatting template for the first line.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value>The formatting line1 template.</value>
    string FormattingLine1Template { get; set; }

    /// <summary>
    /// Gets or sets the formatting template for the second line.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value>The formatting line2 template.</value>
    string FormattingLine2Template { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [view override].
    /// </summary>
    /// <value><c>true</c> if [view override]; otherwise, <c>false</c>.</value>
    bool ViewOverride { get; set; }

    /// <summary>
    /// Gets or sets a value indicating the track duration visibility.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [view duration]; otherwise, <c>false</c>.</value>
    bool ViewDuration { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [view expand buttons].
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [view expand buttons]; otherwise, <c>false</c>.</value>
    bool ViewExpandButtons { get; set; }

    /// <summary>
    /// Gets or sets a value indicating the marks visibility.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [view marks]; otherwise, <c>false</c>.</value>
    bool ViewMarks { get; set; }

    /// <summary>
    /// Gets or sets a value indicating the tracks number visibility.
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [view numbers]; otherwise, <c>false</c>.</value>
    bool ViewNumbers { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [view absolute numbers].
    /// </summary>
    /// <value><c>true</c> if [view absolute numbers]; otherwise, <c>false</c>.</value>
    bool ViewAbsoluteNumbers { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [view second line].
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [view second line]; otherwise, <c>false</c>.</value>
    bool ViewSecondLine { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether [view switches].
    /// <para>
    /// Changing the value is available only if value of the <see cref="GroupingOverridden" /> parameter set as true.
    /// </para>
    /// </summary>
    /// <value><c>true</c> if [view switches]; otherwise, <c>false</c>.</value>
    bool ViewSwitches { get; set; }

    /// <summary>
    /// Gets or sets the index of focused playlist item.
    /// Index can be equals to -1, if no one item is focused.
    /// Use the AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT property to access to focused group.
    /// </summary>
    /// <value>The index of the focus.</value>
    int FocusIndex { get; set; }

    /// <summary>
    /// Gets or sets the playback cursor.
    /// Can be equals to -1, if playable item was removed or playlist never played.
    /// </summary>
    /// <value>The playback cursor.</value>
    int PlaybackCursor { get; set; }

    /// <summary>
    /// Gets or sets the index of the playing.
    /// </summary>
    /// <value>The index of the playing.</value>
    int PlayingIndex { get; set; }

    /// <summary>
    /// Gets the total duration, in seconds.
    /// </summary>
    /// <value>The duration.</value>
    double Duration { get; }

    /// <summary>
    /// Gets the total size, in bytes.
    /// </summary>
    /// <value>The size.</value>
    double Size { get; }

    /// <summary>
    /// Gets or sets the preimage factory.
    /// </summary>
    /// <value>The pre image.</value>
    IAimpPlaylistPreimage PreImage { get; set; }

    /// <summary>
    /// Adds the specified file by URL.
    /// </summary>
    /// <param name="fileUrl">The file URL.</param>
    /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
    /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Add(string fileUrl, PlaylistFlags flags, PlaylistFilePosition filePosition);

    /// <summary>
    /// Adds the specified file by URL.
    /// </summary>
    /// <param name="fileInfo">The file information.</param>
    /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
    /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Add(IAimpFileInfo fileInfo, PlaylistFlags flags, PlaylistFilePosition filePosition);

    /// <summary>
    /// Adds the list.
    /// </summary>
    /// <param name="fileUrlList">The file URL list.</param>
    /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
    /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult AddList(IList<string> fileUrlList, PlaylistFlags flags, PlaylistFilePosition filePosition);

    /// <summary>
    /// Adds the list.
    /// </summary>
    /// <param name="fileUrlList">The file URL list.</param>
    /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
    /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult AddList(IList<IAimpFileInfo> fileUrlList, PlaylistFlags flags,
        PlaylistFilePosition filePosition);

    /// <summary>
    /// Deletes the specified item.
    /// </summary>
    /// <param name="item">The playlist item.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Delete(IAimpPlaylistItem item);

    /// <summary>
    /// Deletes the item by specified index.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Delete(int index);

    /// <summary>
    /// Deletes the specified delete flags.
    /// </summary>
    /// <param name="deleteFlags">The delete flags <see cref="PlaylistDeleteFlags" />.</param>
    /// <param name="customFilterData">Some additional data that will be passed to the filter function.</param>
    /// <param name="filterFunc">The filter function. Should return true to delete item.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Delete(PlaylistDeleteFlags deleteFlags, object customFilterData,
        Func<IAimpPlaylistItem, object, bool> filterFunc);

    /// <summary>
    /// Deletes all items.
    /// </summary>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult DeleteAll();

    /// <summary>
    /// Sorts the playlist by specified sort order.
    /// </summary>
    /// <param name="sort">The sort.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Sort(PlaylistSort sort);

    /// <summary>
    /// Sorts the playlist items by specified template.
    /// </summary>
    /// <param name="template">The template. Refer to <see cref="IAimpServiceFileInfoFormatter" />.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Sort(string template);

    /// <summary>
    /// Sorts the playlist by the specified compare function.
    /// </summary>
    /// <param name="customCompareData">The custom data for compare function.</param>
    /// <param name="compareFunc">The compare function.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Sort(object customCompareData,
        Func<IAimpPlaylistItem, IAimpPlaylistItem, object, PlaylistSortCompareResult> compareFunc);

    /// <summary>
    /// Method blocks all notifications until EndUpdate is called.
    /// This method is recommended to usage if you will change few options of playlist at one time.
    /// </summary>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult BeginUpdate();

    /// <summary>
    /// Method unblocks all notifications. Refer to the BeginUpdate.
    /// </summary>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult EndUpdate();

    /// <summary>
    /// Closes the playlist.
    /// </summary>
    /// <param name="closeFlag">The close flag <see cref="PlaylistCloseFlag" />.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Close(PlaylistCloseFlag closeFlag);

    /// <summary>
    /// Gets the list of files.
    /// </summary>
    /// <param name="filesFlag">The files flag.</param>
    /// <returns>AimpActionResult&lt;IList&lt;System.String&gt;&gt;.</returns>
    AimpActionResult<IList<string>> GetFiles(PlaylistGetFilesFlag filesFlag);

    /// <summary>
    /// Merges one or all groups with same names.
    /// </summary>
    /// <param name="playlistGroup">Group to merge. All groups will be merged If group is not set (parameter is equals null).</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult MergeGroup(IAimpPlaylistGroup playlistGroup);

    /// <summary>
    /// Reloads from preimage.
    /// </summary>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult ReloadFromPreimage();

    /// <summary>
    /// Reloads information about items (running in separate thread).
    /// </summary>
    /// <param name="fullReload">if set to <c>true</c> [full reload].</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult ReloadInfo(bool fullReload);

    /// <summary>
    /// Gets the item.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>AimpActionResult&lt;IAimpPlaylistItem&gt;.</returns>
    AimpActionResult<IAimpPlaylistItem> GetItem(int index);

    /// <summary>
    /// Gets the item count.
    /// </summary>
    /// <returns>System.Int32.</returns>
    int GetItemCount();

    /// <summary>
    /// Gets the group.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>AimpActionResult&lt;IAimpPlaylistGroup&gt;.</returns>
    AimpActionResult<IAimpPlaylistGroup> GetGroup(int index);

    /// <summary>
    /// Gets the group count.
    /// </summary>
    /// <returns>System.Int32.</returns>
    int GetGroupCount();
}