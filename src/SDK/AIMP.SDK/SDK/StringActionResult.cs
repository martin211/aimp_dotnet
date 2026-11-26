using AIMP.SDK.Objects;

namespace AIMP.SDK;

public sealed class StringActionResult : AimpActionResult<IAimpString>
{
    /// <inheritdoc />
    public StringActionResult(ActionResultType resultType) : base(resultType)
    {
    }

    /// <inheritdoc />
    public StringActionResult(ActionResultType resultType, IAimpString result) : base(resultType, result)
    {
    }
}