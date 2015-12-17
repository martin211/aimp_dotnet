namespace AIMP.SDK.Threading
{
    public interface IAimpAsyncTask
    {
        AimpActionResult Execute(IAimpAsyncTaskOwner owner);
    }
}