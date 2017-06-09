using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.DotNet.MusicLibrary.ExplorerGroupingProvider
{
    public class DataProviderGroupingTreeSelection : IAimpGroupingTreeDataProviderSelection
    {
        private readonly DataProviderGroupingTreeData _data;
        private int _index;

        public DataProviderGroupingTreeSelection(DataProviderGroupingTreeData data)
        {
            _data = data;
        }

        public AimpActionResult GetDisplayValue(out string displayValue)
        {
            displayValue = _data[_index].DisplayValue;
            return AimpActionResult.Ok;
        }

        public GroupingTreeNodeFlags GetFlags()
        {
            GroupingTreeNodeFlags result = 0;

            if (_data[_index].Standalone)
            {
                result = GroupingTreeNodeFlags.AIMPML_GROUPINGTREENODE_FLAG_STANDALONE;
            }

            if (_data[_index].HasChildren)
            {
                result |= GroupingTreeNodeFlags.AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN;
            }

            return result;
        }

        public AimpActionResult GetImageIndex(out FieldImageIndex imageIndex)
        {
            imageIndex = (FieldImageIndex)_data[_index].ImageIndex;
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetValue(out string fieldName, out object value)
        {
            fieldName = DemoMusicLibrary.FieldNode;
            value = _data[_index].Value;
            return AimpActionResult.Ok;
        }

        public bool NextRow()
        {
            _index++;
            return _index < _data.Count;
        }
    }
}