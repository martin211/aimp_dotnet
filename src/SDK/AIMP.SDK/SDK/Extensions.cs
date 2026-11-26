namespace AIMP.SDK;

/// <summary>
/// Class Extensions.
/// </summary>
public static class Extensions
{
    /// <summary>
    /// Creates the Aimp object.
    /// </summary>
    /// <typeparam name="TAimpObject">The type of the t aimp object.</typeparam>
    /// <param name="core">The core.</param>
    /// <returns>AimpActionResult&lt;TAimpObject&gt;.</returns>
    public static AimpActionResult<TAimpObject> CreateAimpObject<TAimpObject>(this IAimpCore core)
        where TAimpObject : class, IAimpObject
    {
        var result = core.CreateObject<TAimpObject>();
        return result.ResultType != ActionResultType.OK
            ? new AimpActionResult<TAimpObject>(result.ResultType, null)
            : new AimpActionResult<TAimpObject>(result.ResultType, result.Result as TAimpObject);
    }

    /// <summary>
    /// Creates the Aimp object.
    /// </summary>
    /// <typeparam name="TAimpObject">The type of the aimp object.</typeparam>
    /// <param name="core">The core.</param>
    /// <param name="type">The type.</param>
    public static AimpActionResult<TAimpObject> CreateAimpObject<TAimpObject>(this IAimpCore core,
        AimpObjectType type)
        where TAimpObject : class, IAimpObject
    {
        var result = core.CreateObject(type);
        return result.ResultType != ActionResultType.OK
            ? new AimpActionResult<TAimpObject>(result.ResultType, null)
            : new AimpActionResult<TAimpObject>(result.ResultType, result.Result as TAimpObject);
    }
}