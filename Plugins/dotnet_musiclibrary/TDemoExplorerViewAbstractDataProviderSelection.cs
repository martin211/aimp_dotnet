using System;
using System.IO;
using System.Linq;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;

namespace dotnet_musiclibrary
{
    public abstract class TDemoExplorerViewAbstractDataProviderSelection : IAimpDataProviderSelection
    {
        public virtual double GetValueAsFloat(int fieldIndex)
        {
            return 0;
        }

        public virtual int GetValueAsInt32(int fieldIndex)
        {
            return 0;
        }

        public virtual long GetValueAsInt64(int fieldIndex)
        {
            return 0;
        }

        public virtual string GetValueAsString(int fieldIndex)
        {
            throw new System.NotImplementedException();
        }

        public bool HasNextPage()
        {
            return false;
        }

        public abstract bool NextRow();
    }

    public abstract class TDemoExplorerViewCustomDataProviderSelection : TDemoExplorerViewAbstractDataProviderSelection
    {
        private string _rootPath;

        protected TDemoExplorerViewCustomDataProviderSelection(string apath)
        {

        }

        public override bool NextRow()
        {
            return true;
        }
    }

    public class TDemoExplorerViewGroupingTreeDrivesProvider : TDemoExplorerViewAbstractDataProviderSelection
    {
        private DriveInfo[] _drivers;
        private int _index = 0;
        private DriveInfo _currentDrive;

        public TDemoExplorerViewGroupingTreeDrivesProvider()
        {
            _drivers = DriveInfo.GetDrives();
            _currentDrive = _drivers[_index];
        }

        public override string GetValueAsString(int fieldIndex)
        {
            return _currentDrive.Name;
        }

        public override bool NextRow()
        {
            if (_index < _drivers.Length)
            {
                _index++;
                _currentDrive = _drivers[_index];
            }

            return _index < _drivers.Length;
        }
    }

    public class TDemoExplorerViewGroupingTreeFoldersProvider : TDemoExplorerViewCustomDataProviderSelection
    {
        public TDemoExplorerViewGroupingTreeFoldersProvider(string apath) : base(apath)
        {
        }

        public override string GetValueAsString(int fieldIndex)
        {
            return string.Empty;
        }
    }
}