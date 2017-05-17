using System;
using System.Collections.Generic;

using AIMP.SDK.FileManager;

namespace AIMP.SDK.PlayList
{
    [Flags]
    public enum PlayListFlags
    {
        /// <summary>
        /// suppresses file format checking.
        /// </summary>
        NOCHECKFORMAT = 1,

        /// <summary>
        /// suppresses file expansion to few virtual files.
        /// </summary>
        NOEXPAND = 2,

        /// <summary>
        /// File adding will be processed in main thread, the method will not return control until operation has been completed (not recommended).
        /// </summary>
        NOASYNC = 4,

        /// <summary>
        /// Shows that object is <see cref="IAimpFileInfo"/> (otherwise object must be a string).
        /// </summary>
        FILEINFO = 8
    }

    public enum PlayListFilePosition
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

    public enum PlayListSort
    {
        TITLE,
        FILENAME,
        DURATION,
        ARTIST,
        INVERSE,
        RANDOMIZE
    }

    [Flags]
    public enum PlayListCloseFlag
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
    public enum PlayListGetFilesFlag
    {
        All = 0,

        SelectedOnly = 0x1,

        VisibleOnly = 0x2,
        /// <summary>
        /// In this case, the file-container will be added to the list if playlist item is virtual file.
        /// </summary>
        CollapseVirtual = 0x4
    }

    public enum PlayListSortComapreResult
    {
        TheSame = 0,
        LessThen = -1,
        GrantThen = 1
    }

    [Flags]
    public enum PlayListNotifyType
    {
        /// <summary>
        /// Play list name has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_NAME = 1,

        /// <summary>
        /// Selected items has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_SELECTION      = 2,

        /// <summary>
        /// Playback focus has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_PLAYBACKCURSOR = 4,

        /// <summary>
        /// Read only flag has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_READONLY       = 8,

        /// <summary>
        /// Record focus has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_FOCUSINDEX     = 16,

        /// <summary>
        /// Changed records order.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_CONTENT        = 32,

        /// <summary>
        /// Information about one or more files has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_FILEINFO       = 64,

        /// <summary>
        /// Statistic for one or more files has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_STATISTICS     = 128,

        /// <summary>
        /// Changed auto play switch.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_PLAYINGSWITCHS = 256,

        /// <summary>
        /// Path to pre image has been changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_PREIMAGE       = 512
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

    /// <summary>
    /// Playlist interface.
    /// </summary>
    public interface IAimpPlaylist : IAimpPlaylistListener
    {
        //event AimpPlayListHandler Activated;

        //event AimpPlayListHandler Removed;

        //event PlayListChangedHandler Changed;

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
        object FocusedObject { get; set; }

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
        bool FormatingOverride { get; set; }

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
        /// Gets or sets the pre image.
        /// </summary>
        string PreImage { get; set; }

        /// <summary>
        /// Adds the specified file by URL.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="flags">The <see cref="PlayListFlags"/>.</param>
        /// <param name="filePosition">The file position <see cref="PlayListFilePosition"/>.</param>
        /// <returns></returns>
        AimpActionResult Add(string fileUrl, PlayListFlags flags, PlayListFilePosition filePosition);

        /// <summary>
        /// Adds the specified file by URL.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="flags">The <see cref="PlayListFlags" />.</param>
        /// <param name="filePosition">The file position <see cref="PlayListFilePosition" />.</param>
        /// <returns></returns>
        AimpActionResult Add(IAimpFileInfo fileInfo, PlayListFlags flags, PlayListFilePosition filePosition);

        /// <summary>
        /// Adds the list.
        /// </summary>
        /// <param name="fileUrlList">The file URL list.</param>
        /// <param name="flags">The <see cref="PlayListFlags" />.</param>
        /// <param name="filePosition">The file position <see cref="PlayListFilePosition" />.</param>
        /// <returns></returns>
        AimpActionResult AddList(IList<string> fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

        /// <summary>
        /// Adds the list.
        /// </summary>
        /// <param name="fileUrlList">The file URL list.</param>
        /// <param name="flags">The <see cref="PlayListFlags" />.</param>
        /// <param name="filePosition">The file position <see cref="PlayListFilePosition" />.</param>
        /// <returns></returns>
        AimpActionResult AddList(IList<IAimpFileInfo> fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

        /// <summary>
        /// Deletes the specified item.
        /// </summary>
        /// <param name="item">The playlist item.</param>
        /// <returns></returns>
        AimpActionResult Delete(IAimpPlayListItem item);

        /// <summary>
        /// Deletes the item by specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        AimpActionResult Delete(int index);

        // TODO: implement Delete3
        //void Delete(bool physically);

        /// <summary>
        /// Deletes all items.
        /// </summary>
        /// <returns></returns>
        AimpActionResult DeleteAll();

        /// <summary>
        /// Sorts the playlist by specified sort order.
        /// </summary>
        /// <param name="sort">The sort.</param>
        /// <returns></returns>
        AimpActionResult Sort(PlayListSort sort);

        /// <summary>
        /// Sorts the playlist by the specified compare function.
        /// </summary>
        /// <param name="compareFunc">The compare function.</param>
        /// <returns></returns>
        AimpActionResult Sort(Func<IAimpPlayListItem, IAimpPlayListItem, PlayListSortComapreResult> compareFunc);

        //TODO: implement Sort2, Sort3
        //void Sort();

        /// <summary>
        /// Method blocks all notifications until EndUpdate is called.
        /// This method is recommended to usage if you will change few options of playlist at one time.
        /// </summary>
        /// <returns></returns>
        AimpActionResult BeginUpdate();

        /// <summary>
        /// Method unblocks all notifications. Refer to the BeginUpdate.
        /// </summary>
        /// <returns></returns>
        AimpActionResult EndUpdate();

        /// <summary>
        /// Closes the playlist.
        /// </summary>
        /// <param name="closeFlag">The close flag <see cref="PlayListCloseFlag"/>.</param>
        /// <returns></returns>
        AimpActionResult Close(PlayListCloseFlag closeFlag);

        /// <summary>
        /// Gets the list of files.
        /// </summary>
        /// <param name="filesFlag">The files flag.</param>
        /// <returns></returns>
        IList<string> GetFiles(PlayListGetFilesFlag filesFlag);

        // TODO: Add MergeGroup

        /// <summary>
        /// Reloads from preimage.
        /// </summary>
        /// <returns></returns>
        AimpActionResult ReloadFromPreimage();

        /// <summary>
        /// Reloads information about items (running in separate thread).
        /// </summary>
        /// <param name="fullReload">if set to <c>true</c> [full reload].</param>
        /// <returns></returns>
        AimpActionResult ReloadInfo(bool fullReload);

        /// <summary>
        /// Gets the item.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        IAimpPlayListItem GetItem(int index);

        /// <summary>
        /// Gets the item count.
        /// </summary>
        int GetItemCount();

        /// <summary>
        /// Gets the group.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        IAimpPlayListGroup GetGroup(int index);

        /// <summary>
        /// Gets the group count.
        /// </summary>
        /// <returns></returns>
        int GetGroupCount();
    }
}