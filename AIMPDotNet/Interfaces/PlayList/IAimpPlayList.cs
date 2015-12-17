namespace AIMP.SDK.Services.PlayList
{
    using System;
    using System.Collections.Generic;

    [Flags]
    public enum PlayListFlags
    {
        NOCHECKFORMAT = 1,

        NOEXPAND = 2,

        NOASYNC = 4,

        FILEINFO = 8
    }

    public enum PlayListFilePosition
    {
        RandomPosition = -2,

        EndPosition = -1,

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

        ForceRemove = 1,

        ForceUnload = 2
    }

    [Flags]
    public enum PlayListGetFilesFlag
    {
        All = 0,

        SelectedOnly = 0x1,

        VisibleOnly = 0x2,

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
        /// Record focus hass benn changed.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_FOCUSINDEX     = 16,

        /// <summary>
        /// Changed records order.
        /// </summary>
        AIMP_PLAYLIST_NOTIFY_CONTENT        = 32,

        /// <summary>
        /// Information obout one or more files has been changed.
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


    public delegate void PlayListChangedHandler(IAimpPlayList sender, PlayListNotifyType notifType);

    public delegate void AimpPlayListHandler(IAimpPlayList sender);

    public interface IAimpPlayList
    {
        event AimpPlayListHandler Activated;

        event AimpPlayListHandler Removed;

        event PlayListChangedHandler Changed;

        /// <summary>
        /// Gets the identifier.
        /// </summary>
        /// <value>
        /// The identifier.
        /// </value>
        string Id { get; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>
        /// The name.
        /// </value>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [read only].
        /// </summary>
        bool ReadOnly { get; set; }

        object FocusedObject { get; set; }

        bool GrouppingOvveriden { get; set; }

        bool Groupping { get; set; }

        string GrouppingTemplate { get; set; }

        bool GrouppingAutomerging { get; set; }

        bool FormatingOverride { get; set; }

        string FirstLineTemplate { get; set; }

        string SecondLineTemplate { get; set; }

        bool ViewOverride { get; set; }

        bool ShowDuration { get; set; }

        bool ShowExpandButtons { get; set; }

        bool ShowMarks { get; set; }

        bool ShowNumbers { get; set; }

        bool ShowAbsoluteNumbers { get; set; }

        bool ShowSecondLine { get; set; }

        bool ShowSwitches { get; set; }

        int SelectedIndex { get; set; }

        int PlaybackCursor { get; set; }

        int PlayingIndex { get; set; }

        double Duration { get; }

        double Size { get; }

        string PreImage { get; set; }

        AimpActionResult Add(string fileUrl, PlayListFlags flags, PlayListFilePosition filePosition);

        AimpActionResult Add(IAimpFileInfo fileInfo, PlayListFlags flags, PlayListFilePosition filePosition);

        AimpActionResult AddList(IList<string> fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

        AimpActionResult AddList(IList<IAimpFileInfo> fileUrlList, PlayListFlags flags, PlayListFilePosition filePosition);

        AimpActionResult Delete(IAimpPlayListItem item);

        AimpActionResult Delete(int index);

        // TODO: implement Delete3
        //void Delete(bool physically);

        AimpActionResult DeleteAll();

        AimpActionResult Sort(PlayListSort sort);

        AimpActionResult Sort(Func<IAimpPlayListItem, IAimpPlayListItem, PlayListSortComapreResult> compareFunc);

        //TODO: implement Sort2, Sort3
        //void Sort();

        AimpActionResult BeginUpdate();

        AimpActionResult EndUpdate();

        AimpActionResult Close(PlayListCloseFlag closeFlag);

        IList<string> GetFiles(PlayListGetFilesFlag filesFlag);

        // TODO: Add MergeGroup

        AimpActionResult ReloadFromPreimage();

        AimpActionResult ReloadInfo(bool fullReload);

        IAimpPlayListItem GetItem(int index);

        int GetItemCount();

        IAimpPlayListGroup GetGroup(int index);

        int GetGroupCount();
    }
}