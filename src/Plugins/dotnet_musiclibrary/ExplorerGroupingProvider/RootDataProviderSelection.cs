using System.Collections.Generic;
using AIMP.SDK.MusicLibrary;

namespace Aimp.MusicLibraryPlugin.ExplorerGroupingProvider
{
    public class RootDataProviderSelection : IAimpDataProviderSelection
    {
        private readonly IAimpDataFilter _aimpDataFilter;
        private readonly DataProviderGroupingTreeData _data;
        private readonly IList<string> _fields;
        private int _index;

        public RootDataProviderSelection(IList<string> fields, IAimpDataFilter aimpDataFilter,
            DataProviderGroupingTreeData data)
        {
            _fields = fields;
            _aimpDataFilter = aimpDataFilter;
            _data = data;
        }

        public double GetValueAsFloat(int fieldIndex)
        {
            return _data.ReadDouble(fieldIndex);
        }

        public int GetValueAsInt32(int fieldIndex)
        {
            return _data.ReadInt(fieldIndex);
        }

        public long GetValueAsInt64(int fieldIndex)
        {
            return _data.ReadInt(fieldIndex);
        }

        public string GetValueAsString(int fieldIndex)
        {
            return _data.ReadString(fieldIndex);
        }

        public bool HasNextPage()
        {
            return _index < _data.Count;
        }

        public bool NextRow()
        {
            var res = _index < _data.Count;
            _index++;
            return res;
        }
    }
}
