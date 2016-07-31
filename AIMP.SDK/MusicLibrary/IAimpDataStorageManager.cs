using AIMP.SDK.ActionManager;

namespace AIMP.SDK.MusicLibrary
{
    public interface IAimpDataStorageManager
    {
        AimpActionResult BackgroundTaskStarted(int id, string caption, IAimpActionEvent cancelEvent);

        AimpActionResult BackgroundTaskFinished(int id);

        void Changed();
    }
}