
namespace AIMP.SDK.PlayList
{
    public interface IAimpPlayListItem : IAimpDisposeable
    {
        string DisplayText { get; }

        IAimpFileInfo FileInfo { get; }

        string FileName { get; set; }

        IAimpPlayListGroup Group { get; }

        int Index { get; set; }

        double Mark { get; set; }

        int PlaybackIndex { get; }

        bool PlaybackSwitch { get; set; }

        IAimpPlayList PlayList { get; set; }

        bool Selected { get; set; }

        AimpActionResult ReloadInfo();
    }
}