using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataProvider
    {
        AimpActionResult GetData(IList<string> fields, IAimpDataFilter filter, out object data);
    }
}