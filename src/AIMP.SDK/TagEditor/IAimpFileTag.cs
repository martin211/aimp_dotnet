using AIMP.SDK.FileManager;

namespace AIMP.SDK.TagEditor
{
    public interface IAimpFileTag : IAimpFileInfo
    {
        TagType TagId { get; set; }

        bool DeleteOnSaving { get; set; }
    }
}