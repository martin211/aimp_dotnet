namespace AIMP.SDK.Objects;

/// <summary>
/// Interface IAimpMemoryStream
/// Implements the <see cref="IAimpStream" />
/// </summary>
/// <seealso cref="IAimpStream" />
public interface IAimpMemoryStream : IAimpStream
{
    /// <summary>
    /// Gets the data.
    /// </summary>
    /// <returns>AimpActionResult&lt;System.Byte[]&gt;.</returns>
    AimpActionResult<byte[]> GetData();
}