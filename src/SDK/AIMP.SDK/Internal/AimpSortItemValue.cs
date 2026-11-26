using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal
{
    /// <summary>
    /// Sort item created from a bare field name. Used by the v1
    /// <c>IAimpGroupingPresets.Add(string, string, IList&lt;string&gt;)</c> overload
    /// where the caller does not specify a direction.
    /// </summary>
    internal sealed class AimpSortItemValue : IAimpSortItem
    {
        public AimpSortItemValue(string fieldName)
        {
            FieldName = fieldName;
            Value = SortDirectionType.Undefined;
        }

        public string FieldName { get; set; }

        public SortDirectionType Value { get; set; }

        public void Dispose()
        {
        }
    }
}