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
        protected string _rootPath;
        private int _index;
        private string[] _directories;
        protected string CurrentItem;

        protected TDemoExplorerViewCustomDataProviderSelection(string apath)
        {
            _rootPath = $"{apath}\\";
            CurrentItem = _rootPath;
            _directories = Directory.GetDirectories(_rootPath, "*");

            while (!CheckRecordAttributes())
            {
                if (!NextRow())
                {
                    break;
                }
            }
        }

        public override bool NextRow()
        {
            bool result = false;

            do
            {
                result = _directories[_index] != null;
                _index++;
            } while (!result || CheckRecordAttributes());

            return result;
        }

        protected string GetDirectory()
        {
            DirectoryInfo di;
            var dir = _directories[_index];
            di = new DirectoryInfo(dir);

            if (!di.Attributes.HasFlag(FileAttributes.Directory))
            {
                return string.Empty;
            }

            if (di.Attributes.HasFlag(FileAttributes.Hidden) || di.Attributes.HasFlag(FileAttributes.System))
            {
                _index++;
                return GetDirectory();
            }

            return dir;
        }

        protected abstract bool CheckRecordAttributes();
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
            return GetDirectory();
        }

        protected override bool CheckRecordAttributes()
        {
            var di = new DirectoryInfo(CurrentItem);
            return di.Attributes.HasFlag(FileAttributes.Directory) && !(di.Attributes.HasFlag(FileAttributes.Hidden) || di.Attributes.HasFlag(FileAttributes.System));
        }
    }

    public class TDemoExplorerViewDataProviderSelection : TDemoExplorerViewCustomDataProviderSelection
    {
        private readonly string[] _fields;

        public TDemoExplorerViewDataProviderSelection(string apath, IEnumerable<string> fields) 
            : base(apath)
        {
            _fields = fields.ToArray();
        }

        public override bool NextRow()
        {
            return true;
        }

        protected override bool CheckRecordAttributes()
        {
            var di = new DirectoryInfo(_rootPath);
            return !di.Attributes.HasFlag(FileAttributes.Directory)
                   && Path.GetExtension(_rootPath).Equals("mp3");
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
            {
                
            }
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