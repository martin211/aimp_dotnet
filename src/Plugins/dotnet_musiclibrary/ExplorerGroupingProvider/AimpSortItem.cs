using AIMP.SDK.MusicLibrary;

namespace Aimp.MusicLibraryPlugin.ExplorerGroupingProvider
{
    public class AimpSortItem : IAimpSortItem
    {
        public SortDirectionType Value { get; set; }

        // Convenience alias used by the demo initializers.
        public SortDirectionType SortDirection
        {
            get => Value;
            set => Value = value;
        }

        public string FieldName { get; set; }

        public void Dispose()
        {
            // TODO release managed resources here
        }
    }
}