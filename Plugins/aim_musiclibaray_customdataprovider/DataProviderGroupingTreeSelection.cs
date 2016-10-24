using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.CustomDataProvider
{
    public class DataProviderGroupingTreeSelection : IAimpGroupingTreeDataProviderSelection
    {
        private readonly DataProviderGroupingTreeData _data;
        private int _index;
        private readonly string _fieldName;

        public DataProviderGroupingTreeSelection(DataProviderGroupingTreeData data)
        {
            _data = data;
            _fieldName = DataStorage.FieldNode;
        }

        public AimpActionResult GetDisplayValue(out string displayValue)
        {
            displayValue = _data[_index].DiaplyValue;
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
            fieldName = _fieldName;
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