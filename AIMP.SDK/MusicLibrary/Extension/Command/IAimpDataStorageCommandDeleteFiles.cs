using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public class AimpFile
    {
        public AimpFile(string name, string id)
        {
            Name = name;
            Id = id;
        }

        public string Name { get; }

        public string Id { get; }
    }

    public interface IAimpDataStorageCommandDeleteFiles
    {
        AimpActionResult CanDelete(bool physically);

        AimpActionResult Delete(IList<AimpFile> files, bool physically);

        AimpActionResult Delete(IAimpDataFilter filter, bool physically);
    }
}