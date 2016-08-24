using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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
            _rootPath = $"{apath}\\";
            var dirs = Directory.GetDirectories(_rootPath, "*");
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
                _currentDrive = _drivers[_index];
                _index++;
            }
            else
            {
                return false;
            }

            return _index - 1 != _drivers.Length;
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

    public class TDemoExplorerViewDataProviderSelection : TDemoExplorerViewCustomDataProviderSelection
    {
        private readonly string[] _fields;

        public TDemoExplorerViewDataProviderSelection(string apath, IEnumerable<string> fields) : base(apath)
        {
            _fields = fields.ToArray();
        }

        public override bool NextRow()
        {
            return true;
        }

        public override double GetValueAsFloat(int fieldIndex)
        {
            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileAccessTime))
            {

            }
            else if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileCreationTime))
            {

            }

            return 0;
        }

        public override long GetValueAsInt64(int fieldIndex)
        {
            return 0;
        }

        public override string GetValueAsString(int fieldIndex)
        {
            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileName))
            { }
            else if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_ID))
            { }

            return string.Empty;
        }

        private int GetIndex(string fieldName)
        {
            return Array.IndexOf(_fields.ToArray(), fieldName);
        }
    }
}