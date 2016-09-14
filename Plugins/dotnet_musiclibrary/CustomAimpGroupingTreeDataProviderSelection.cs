using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace dotnet_musiclibrary
{
    public class CustomAimpGroupingTreeDataProviderSelection : IAimpGroupingTreeDataProviderSelection
    {
        public AimpActionResult GetDisplayValue(out string displayValue)
        {
            displayValue = "Test value";
            return AimpActionResult.Ok;
        }

        public GroupingTreeNodeFlags GetFlags()
        {
            return GroupingTreeNodeFlags.AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN;
        }

        public AimpActionResult GetImageIndex(out FieldImageIndex imageIndex)
        {
            imageIndex = FieldImageIndex.AIMPML_FIELDIMAGE_FOLDER;
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetValue(out string fieldName, out object value)
        {
            fieldName = "fn";
            value = 1;

            return AimpActionResult.Ok;
        }

        public bool NextRow()
        {
            return true;
        }
    }
}