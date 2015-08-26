
namespace AIMP.SDK.Services.PlayListManager
{
    public interface IAimpPlayListItem
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

        ActionResult ReloadInfo();
    }
}