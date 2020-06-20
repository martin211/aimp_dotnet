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
        /// File adding will be processed in main thread, the method will not return control until operation has been completed (not recommended).
        /// </summary>
        NoAsync = 4,

        /// <summary>
        /// Shows that object is <see cref="IAimpFileInfo"/> (otherwise object must be a string).
        /// </summary>
        FileInfo = 8
    }

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

    public enum PlaylistSort
    {
        Title = 1,
        FileName = 2,
        Duration = 3,
        Artist = 4,
        Inverse = 5,
        Randomize = 6
    }

    [Flags]
    public enum PlaylistCloseFlag
    {
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

    [Flags]
    public enum PlaylistGetFilesFlag
    {
        All = 0,

        SelectedOnly = 0x1,

        VisibleOnly = 0x2,

        /// <summary>
        /// In this case, the file-container will be added to the list if playlist item is virtual file.
        /// </summary>
        CollapseVirtual = 0x4
    }

    public enum PlaylistSortComapreResult
    {
        TheSame = 0,
        LessThen = -1,
        GrantThen = 1
    }

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

    [Flags]
    public enum PlaylistDeleteFlags
    {
        None = 0,
        Physically = 1,
        NoConfirmation = 2
    }

    /// <summary>
    /// Playlist interface.
    /// </summary>
    public interface IAimpPlaylist : IAimpPlaylistListener
    {
        /// <summary>
        /// Gets the playlist identifier.
        /// </summary>
        string Id { get; }

        /// <summary>
        /// Gets or sets the playlist name.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets a value indicating playlist is read only..
        /// </summary>
        bool ReadOnly { get; set; }

        /// <summary>
        /// Gets or sets the focused object.
        /// Object should be <see cref="IAimpPlaylistItem"/> or <see cref="IAimpPlaylistGroup"/>.
        /// </summary>
        IAimpPlaylistItem FocusedItem { get; set; }

        IAimpPlaylistGroup FocusedGroup { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [grouping overridden].
        /// </summary>
        bool GroupingOverridden { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpPlaylist"/> is grouping.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool Grouping { get; set; }

        /// <summary>
        /// Gets or sets the grouping template.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        string GroupingTemplate { get; set; }

        /// <summary>
        /// Enables the auto merge for grouping.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool GroupingAutomerg { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [formating override].
        /// </summary>
        bool FormattingOverride { get; set; }

        /// <summary>
        /// Gets or sets the formatting template for the first line.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        string FormattingLine1Template { get; set; }

        /// <summary>
        /// Gets or sets the formatting template for the second line.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        string FormattingLine2Template { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [view override].
        /// </summary>
        bool ViewOverride { get; set; }

        /// <summary>
        /// Gets or sets a value indicating the track duration visibility.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool ViewDuration { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [view expand buttons].
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool ViewExpandButtons { get; set; }

        /// <summary>
        /// Gets or sets a value indicating the marks visibility.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool ViewMarks { get; set; }

        /// <summary>
        /// Gets or sets a value indicating the tracks number visibility.
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool ViewNumbers { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [view absolute numbers].
        /// </summary>
        bool ViewAbsoluteNumbers { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [view second line].
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool ViewSecondLine { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [view switches].
        /// <para>
        /// Changing the value is available only if value of the <see cref="GroupingOverridden"/> parameter set as true.
        /// </para>
        /// </summary>
        bool ViewSwitches { get; set; }

        /// <summary>
        /// Gets or sets the index of focused playlist item.
        /// Index can be equals to -1, if no one item is focused.
        /// Use the AIMP_PLAYLIST_PROPID_FOCUSED_OBJECT property to access to focused group.
        /// </summary>
        int FocusIndex { get; set; }

        /// <summary>
        /// Gets or sets the playback cursor.
        /// Can be equals to -1, if playable item was removed or playlist never played.
        /// </summary>
        int PlaybackCursor { get; set; }

        /// <summary>
        /// Gets or sets the index of the playing.
        /// </summary>
        int PlayingIndex { get; set; }

        /// <summary>
        /// Gets the total duration, in seconds.
        /// </summary>
        double Duration { get; }

        /// <summary>
        /// Gets the total size, in bytes.
        /// </summary>
        double Size { get; }

        /// <summary>
        /// Gets or sets the preimage factory.
        /// </summary>
        IAimpPlaylistPreimage PreImage { get; set; }

        /// <summary>
        /// Adds the specified file by URL.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="flags">The <see cref="PlaylistFlags"/>.</param>
        /// <param name="filePosition">The file position <see cref="PlaylistFilePosition"/>.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Add(string fileUrl, PlaylistFlags flags, PlaylistFilePosition filePosition);

        /// <summary>
        /// Adds the specified file by URL.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
        /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Add(IAimpFileInfo fileInfo, PlaylistFlags flags, PlaylistFilePosition filePosition);

        /// <summary>
        /// Adds the list.
        /// </summary>
        /// <param name="fileUrlList">The file URL list.</param>
        /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
        /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult AddList(IList<string> fileUrlList, PlaylistFlags flags, PlaylistFilePosition filePosition);

        /// <summary>
        /// Adds the list.
        /// </summary>
        /// <param name="fileUrlList">The file URL list.</param>
        /// <param name="flags">The <see cref="PlaylistFlags" />.</param>
        /// <param name="filePosition">The file position <see cref="PlaylistFilePosition" />.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult AddList(IList<IAimpFileInfo> fileUrlList, PlaylistFlags flags, PlaylistFilePosition filePosition);

        /// <summary>
        /// Deletes the specified item.
        /// </summary>
        /// <param name="item">The playlist item.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Delete(IAimpPlaylistItem item);

        /// <summary>
        /// Deletes the item by specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="deleteFlags">The delete flags <see cref="PlaylistDeleteFlags"/>.</param>
        /// <param name="customFilterData">Some additional data that will be passed to the filter function.</param>
        /// <param name="filterFunc">The filter function. Should return true to delete item.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Delete(PlaylistDeleteFlags deleteFlags, object customFilterData, Func<IAimpPlaylistItem, object, bool> filterFunc);

        /// <summary>
        /// Deletes all items.
        /// </summary>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult DeleteAll();

        /// <summary>
        /// Sorts the playlist by specified sort order.
        /// </summary>
        /// <param name="sort">The sort.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Sort(PlaylistSort sort);

        /// <summary>
        /// Sorts the playlist items by specified template.
        /// </summary>
        /// <param name="template">The template. Refer to <see cref="IAimpServiceFileInfoFormatter"/>.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Sort(string template);

        /// <summary>
        /// Sorts the playlist by the specified compare function.
        /// </summary>
        /// <param name="customCompareData">The custom data for compare function.</param>
        /// <param name="compareFunc">The compare function.</param>
        /// <returns>
        /// The <see cref="ActionResultType" /> result.
        /// </returns>
        AimpActionResult Sort(object customCompareData, Func<IAimpPlaylistItem, IAimpPlaylistItem, object, PlaylistSortComapreResult> compareFunc);

        /// <summary>
        /// Method blocks all notifications until EndUpdate is called.
        /// This method is recommended to usage if you will change few options of playlist at one time.
        /// </summary>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult BeginUpdate();

        /// <summary>
        /// Method unblocks all notifications. Refer to the BeginUpdate.
        /// </summary>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult EndUpdate();

        /// <summary>
        /// Closes the playlist.
        /// </summary>
        /// <param name="closeFlag">The close flag <see cref="PlaylistCloseFlag"/>.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult Close(PlaylistCloseFlag closeFlag);

        /// <summary>
        /// Gets the list of files.
        /// </summary>
        /// <param name="filesFlag">The files flag.</param>
        /// <param name="files">The files.</param>
        /// <returns>
        /// The <see cref="ActionResultType" /> result.
        /// </returns>
        AimpActionResult<IList<string>> GetFiles(PlaylistGetFilesFlag filesFlag);

        /// <summary>
        /// Merges one or all groups with same names.
        /// </summary>
        /// <param name="playlistGroup">Group to merge. All groups will be merged If group is not set (parameter is equals null).</param>
        /// <returns>The <see cref="ActionResultType" /> result.</returns>
        ActionResultType MergeGroup(IAimpPlaylistGroup playlistGroup);

        /// <summary>
        /// Reloads from preimage.
        /// </summary>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        ActionResultType ReloadFromPreimage();

        /// <summary>
        /// Reloads information about items (running in separate thread).
        /// </summary>
        /// <param name="fullReload">if set to <c>true</c> [full reload].</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        ActionResultType ReloadInfo(bool fullReload);

        /// <summary>
        /// Gets the item.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult<IAimpPlaylistItem> GetItem(int index);

        /// <summary>
        /// Gets the item count.
        /// </summary>
        int GetItemCount();

        /// <summary>
        /// Gets the group.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        AimpActionResult<IAimpPlaylistGroup> GetGroup(int index);

        /// <summary>
        /// Gets the group count.
        /// </summary>
        /// <returns></returns>
        int GetGroupCount();
    }
}