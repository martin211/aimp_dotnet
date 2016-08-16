using System.Collections;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataProvider
    {
        AimpActionResult GetData(IList fields, IAimpDataFilter filter, out object data);
    }
}