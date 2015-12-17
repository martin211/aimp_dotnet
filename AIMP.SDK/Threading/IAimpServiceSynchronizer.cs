namespace AIMP.SDK.Threading
{
    public interface IAimpServiceSynchronizer
    {
       AimpActionResult ExecuteInMainThread(IAimpAsyncTask task, bool executeNow);
    }
}