namespace AIMP.SDK.Services.Threading
{
    public interface IAimpServiceSynchronizer
    {
       AimpActionResult ExecuteInMainThread(IAimpAsyncTask task, bool executeNow);
    }
}