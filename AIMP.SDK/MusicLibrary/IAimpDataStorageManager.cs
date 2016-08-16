using AIMP.SDK.ActionManager;

namespace AIMP.SDK.MusicLibrary
{
    public interface IAimpDataStorageManager
    {
        void BackgroundTaskStarted(int id, string caption, IAimpActionEvent cancelEvent);

        void BackgroundTaskFinished(int id);

        void Changed();
    }
}