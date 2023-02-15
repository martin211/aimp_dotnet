//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

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

        public AimpActionResult<string> GetDisplayValue()
        {
            return new AimpActionResult<string>(ActionResultType.OK, _data[_index].DisplayValue);
        }

        public GroupingTreeNodeFlags GetFlags()
        {
            GroupingTreeNodeFlags result = 0;

            if (_data[_index].Standalone)
            {
                result = GroupingTreeNodeFlags.Standalone;
            }

            if (_data[_index].HasChildren)
            {
                result |= GroupingTreeNodeFlags.HasChildren;
            }

            return result;
        }

        public AimpActionResult<FieldImageIndex> GetImageIndex()
        {
            return new AimpActionResult<FieldImageIndex>(ActionResultType.OK,
                (FieldImageIndex) _data[_index].ImageIndex);
        }

        public AimpActionResult<string, object> GetValue()
        {
            return new AimpActionResult<string, object>(ActionResultType.OK, DemoMusicLibrary.FieldNode,
                _data[_index].Value);
        }

        public bool NextRecord()
        {
            _index++;
            return _index < _data.Count;
        }
    }
}
