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
using System.Collections.Generic;
using AIMP.SDK.FileManager;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// Enum PlaylistFlags
    /// </summary>
    [Flags]
    public enum PlaylistFlags
    {
        /// <summary>
        /// suppresses file format checking.
        /// </summary>
        NoCheckFormat = 1,

        /// <summary>
        /// suppresses file expansion to few virtual files.
        /// </summary>
        NoExpand = 2,

        /// <summary>
        /// File adding will be processed in main thread, the method will not return control until operation has been completed
        /// (not recommended).
        /// </summary>
        NoAsync = 4,

        /// <summary>
        /// Shows that object is <see cref="IAimpFileInfo" /> (otherwise object must be a string).
        /// </summary>
        FileInfo = 8
    }

    /// <summary>
    /// Enum PlaylistFilePosition
    /// </summary>
    public enum PlaylistFilePosition
    {
        /// <summary>
        /// Adding the records to random position
        /// </summary>
        RandomPosition = -2,

        /// <summary>
        /// Adding the records to the end of playlist.
        /// </summary>
        EndPosition = -1,

        /// <summary>
        /// Adding the records to the specified position.
        /// </summary>
        CurrentPosition = 0
    }

    /// <summary>
    /// Enum PlaylistSort
    /// </summary>
    public enum PlaylistSort
    {
        /// <summary>
        /// The title
        /// </summary>
        Title = 1,

        /// <summary>
        /// The file name
        /// </summary>
        FileName = 2,

        /// <summary>
        /// The duration
        /// </summary>
        Duration = 3,

        /// <summary>
        /// The artist
        /// </summary>
        Artist = 4,

        /// <summary>
        /// The inverse
        /// </summary>
        Inverse = 5,

        /// <summary>
        /// The randomize
        /// </summary>
        Randomize = 6
    }

    /// <summary>
    /// Enum PlaylistCloseFlag
    /// </summary>
    [Flags]
    public enum PlaylistCloseFlag
    {
        /// <summary>
        /// The none
        /// </summary>
        None = 0,

        /// <summary>
        /// Ignores current settings and remove playlist from disk after closing.
        /// </summary>
        ForceRemove = 1,

        /// <summary>
        /// Ignores current settings and not remove playlist from disk after closing.
        /// </summary>
        ForceUnload = 2
    }

    /// <summary>
    /// Enum PlaylistGetFilesFlag
    /// </summary>
    [Flags]
    public enum PlaylistGetFilesFlag
    {
        /// <summary>
        /// All
        /// </summary>
        All = 0,

        /// <summary>
        /// The selected only
        /// </summary>
        SelectedOnly = 0x1,

        /// <summary>
        /// The visible only
        /// </summary>
        VisibleOnly = 0x2,

        /// <summary>
        /// In this case, the file-container will be added to the list if playlist item is virtual file.
        /// </summary>
        CollapseVirtual = 0x4
    }

    /// <summary>
    /// Enum PlaylistSortComapreResult
    /// </summary>
    public enum PlaylistSortComapreResult
    {
        /// <summary>
        /// The same
        /// </summary>
        TheSame = 0,

        /// <summary>
        /// The less then
        /// </summary>
        LessThen = -1,

        /// <summary>
        /// The grant then
        /// </summary>
        GrantThen = 1
    }

    /// <summary>
    /// Enum PlaylistNotifyType
    /// </summary>
    [Flags]
    public enum PlaylistNotifyType
    {
        /// <summary>
        /// Play list name has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_NAME = 1,

        /// <summary>
        /// Selected items has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_SELECTION = 2,

        /// <summary>
        /// Playback focus has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_PLAYBACKCURSOR = 4,

        /// <summary>
        /// Read only flag has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_READONLY = 8,

        /// <summary>
        /// Record focus has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_FOCUSINDEX = 16,

        /// <summary>
        /// Changed records order.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_CONTENT = 32,

        /// <summary>
        /// Information about one or more files has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_FILEINFO = 64,

        /// <summary>
        /// Statistic for one or more files has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_STATISTICS = 128,

        /// <summary>
        /// Changed auto play switch.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_PLAYINGSWITCHS = 256,

        /// <summary>
        /// Path to pre image has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_PREIMAGE = 512
    }

    /// <summary>
    /// Enum ReloadInfoFlags
    /// </summary>
    [Flags]
    public enum ReloadInfoFlags
    {
        /// <summary>
        /// Information will be updated for files that does not have it.
        /// </summary>
        AIMP_PLAYLIST_RELOADINFO_FLAGS_DEFAULT,

        /// <summary>
        /// Information will be updated for all files.
        /// </summary>
        AIMP_PLAYLIST_RELOADINFO_FLAGS_FULL,

        /// <summary>
        /// Information will be updated for selected files.
        /// </summary>
        AIMP_PLAYLIST_RELOADINFO_FLAGS_SELECTED
    }

    /// <summary>
    /// Enum PlaylistDeleteFlags
    /// </summary>
    [Flags]
    public enum PlaylistDeleteFlags
    {
        /// <summary>
        /// The none
        /// </summary>
        None = 0,

        /// <summary>
        /// The physically
        /// </summary>
        Physically = 1,

        /// <summary>
        /// The no confirmation
        /// </summary>
        NoConfirmation = 2
    }

    /// <summary>
    /// Playlist interface.
    /// Implements the <see cref="AIMP.SDK.Playlist.IAimpPlaylistListener" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.Playlist.IAimpPlaylistListener" />
    public interface IAimpPlaylist : IAimpPlaylistListener
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
            Func<IAimpPlaylistItem, IAimpPlaylistItem, object, PlaylistSortComapreResult> compareFunc);

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
}