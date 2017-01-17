namespace AIMP.SDK.Threading
{
    public enum AimpTaskPriority
    {
        Normal,
        Low,
        Hight
    }

    public interface IAimpTaskPriority
    {
        AimpTaskPriority GetPriority();
    }
}