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
        private List<string> _items = new List<string>();
        protected string CurrentItem;

        protected TDemoExplorerViewCustomDataProviderSelection(string apath)
        {
            _rootPath = $@"{apath}";

            System.Diagnostics.Debug.WriteLine(_rootPath);

            var dirs = Directory.GetDirectories(_rootPath, "*");
            if (dirs != null && dirs.Any())
            {
                _items.AddRange(dirs);
            }

            //var files = Directory.GetFiles(_rootPath, "*");
            //if (files != null && files.Any())
            //{
            //    _items.AddRange(files);
            //}

            if (_items.Any())
            {
                CurrentItem = _items[_index];
            }

            //while (!CheckRecordAttributes())
            //{
            //    if (!NextRow())
            //    {
            //        break;
            //    }
            //}
        }

        public override bool NextRow()
        {
            _index++;
            bool result = _index < _items.Count;

            if (result)
            {
                CurrentItem = _items[_index];
            }

            //do
            //{
            //    _index++;
            //    result = _index < _items.Count;
            //    if (result)
            //    {
            //        CurrentItem = _items[_index];
            //    }
            //} while (result || CheckRecordAttributes());

            return result;
        }

        protected string GetDirectory()
        {
            DirectoryInfo di;
            var dir = _items[_index];
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
            var drivers = DriveInfo.GetDrives().Where(c => c.DriveType == DriveType.Fixed).ToArray();
            _drivers = new DriveInfo[]
            {
                drivers.First()
            };

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
            return $@"{CurrentItem}\";
        }

        protected override bool CheckRecordAttributes()
        {
            var di = new DirectoryInfo(CurrentItem);
            return di.Attributes.HasFlag(FileAttributes.Directory) && !di.Attributes.HasFlag(FileAttributes.System);
                // && !(di.Attributes.HasFlag(FileAttributes.Hidden) || di.Attributes.HasFlag(FileAttributes.System));
        }
    }

    public class TDemoExplorerViewDataProviderSelection : TDemoExplorerViewCustomDataProviderSelection
    {
        private readonly string[] _fields;

        private const string _ext = "*.aiff;*.aif;*.ogg;*.oga;*.wav;*.mp3;*.mp2;*.mp1;*.mpga;*.umx;*.mod;*.mo3;*.it;*.s3m;*.mtm;*.xm;*.w64;*.cda;*.iso;*.dff;*.dsf;*.aac;*.m4a;*.m4b;*.mp4;*.ac3;*.ape;*.mac;*.flac;*.fla;*.midi;*.mid;*.rmi;*.kar;*.mpc;*.mp+;*.mpp;*.opus;*.spx;*.tta;*.wma;*.wv;*.tak;";

        public TDemoExplorerViewDataProviderSelection(string apath, IEnumerable<string> fields) 
            : base(apath)
        {
            _fields = fields.ToArray();
        }

        protected override bool CheckRecordAttributes()
        {
            var di = new DirectoryInfo(_rootPath);
            return !di.Attributes.HasFlag(FileAttributes.Directory)
                   && _ext.Contains($"{Path.GetExtension(_rootPath)};");
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