namespace AIMP.SDK.Threading
{
    public interface IAimpTask
    {
        AimpActionResult Execute(IAimpTaskOwner owner);
    }
}