// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

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

        public ActionResultType GetDisplayValue(out string displayValue)
        {
            displayValue = _data[_index].DisplayValue;
            return ActionResultType.OK;
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

        public ActionResultType GetImageIndex(out FieldImageIndex imageIndex)
        {
            imageIndex = (FieldImageIndex)_data[_index].ImageIndex;
            return ActionResultType.OK;
        }

        public ActionResultType GetValue(out string fieldName, out object value)
        {
            fieldName = DemoMusicLibrary.FieldNode;
            value = _data[_index].Value;
            return ActionResultType.OK;
        }

        public bool NextRow()
        {
            _index++;
            return _index < _data.Count;
        }
    }
}