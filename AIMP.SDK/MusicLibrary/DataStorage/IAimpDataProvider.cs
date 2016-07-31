using System.Collections;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataProvider
    {
        AimpActionResult GetData(IEnumerable fields, IAimpDataFilter filter, out object data);
    }
}