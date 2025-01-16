using AIMP.SDK.MusicLibrary;

namespace AIMP.DotNet.MusicLibrary.ExplorerGroupingProvider
{
    public class AimpSortItem : IAimpSortItem
    {
        public SortDirectionType SortDirection { get; set; }

        public string FieldName { get; set; }

        public void Dispose()
        {
            // TODO release managed resources here
        }
    }
}