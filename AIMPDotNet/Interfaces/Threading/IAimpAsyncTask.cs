namespace AIMP.SDK.Services.Threading
{
    using AIMP.SDK.Annotations;

    public interface IAimpAsyncTask
    {
        AimpActionResult Execute(IAimpAsyncTaskOwner owner);
    }
}