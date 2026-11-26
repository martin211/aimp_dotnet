namespace AIMP.SDK.Objects;

/// <summary>
/// Configuration file that can load/save its values from/to a file or a stream
/// (AIMP 6.0+).
/// </summary>
public interface IAimpConfigFile : IAimpConfig
{
    AimpActionResult LoadFromFile(string fileName);

    AimpActionResult LoadFromStream(IAimpStream stream);

    AimpActionResult SaveToFile(string fileName);

    AimpActionResult SaveToStream(IAimpStream stream);
}