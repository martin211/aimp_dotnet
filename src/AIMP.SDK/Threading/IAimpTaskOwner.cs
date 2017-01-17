namespace AIMP.SDK.Threading
{
    public interface IAimpTaskOwner
    {
        bool IsCanceled { get; }
    }
}