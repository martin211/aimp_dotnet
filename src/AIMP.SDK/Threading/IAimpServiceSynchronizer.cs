namespace AIMP.SDK.Threading
{
    public interface IAimpServiceSynchronizer
    {
       AimpActionResult ExecuteInMainThread(IAimpTask task, bool executeNow);
    }
}