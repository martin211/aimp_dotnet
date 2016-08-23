using System;
using System.IO;
using System.Linq;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;

namespace dotnet_musiclibrary
{
    public class TDemoExplorerViewGroupingTreeFoldersProvider : IAimpDataProviderSelection
    {
        private int _index;
        private DriveInfo _currentDriver;
        private DriveInfo[] _allDrives;

        public TDemoExplorerViewGroupingTreeFoldersProvider()
        {
            _index = 0;
            _allDrives = DriveInfo.GetDrives();
            _currentDriver = _allDrives[_index];
        }

        public double GetValueAsFloat(int fieldIndex)
        {
            return 0;
        }

        public int GetValueAsInt32(int fieldIndex)
        {
            return 0;
        }

        public long GetValueAsInt64(int fieldIndex)
        {
            return 0;
        }

        public string GetValueAsString(int fieldIndex)
        {
            throw new System.NotImplementedException();
        }

        public AimpActionResult HasNextPage()
        {
            return AimpActionResult.Ok;
        }

        public bool NextRow()
        {
            return _index != _allDrives.Length - 1;
        }
    }
}