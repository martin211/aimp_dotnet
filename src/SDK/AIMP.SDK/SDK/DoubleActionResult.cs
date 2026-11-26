namespace AIMP.SDK;

public sealed class DoubleActionResult : AimpActionResult<double>
{
    public DoubleActionResult(ActionResultType resultType) : base(resultType)
    {
    }

    public DoubleActionResult(ActionResultType resultType, double result) : base(resultType, result)
    {
    }
}