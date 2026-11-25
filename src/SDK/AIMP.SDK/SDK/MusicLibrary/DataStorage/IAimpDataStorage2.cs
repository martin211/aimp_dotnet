namespace AIMP.SDK.MusicLibrary.DataStorage;

public interface IAimpDataStorage2 : IAimpDataStorage
{
    /// <summary>
    /// Creates the object.
    /// Supports only <see cref="IAimpDataFilter"/>.
    /// </summary>
    /// <returns></returns>
    AimpActionResult<object> CreateObject();
}