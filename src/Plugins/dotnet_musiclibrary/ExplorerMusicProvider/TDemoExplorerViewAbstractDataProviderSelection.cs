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

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using AIMP.SDK.MusicLibrary;

namespace AIMP.DotNet.MusicLibrary.ExplorerMusicProvider
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
        protected int _index;
        protected List<string> _items = new List<string>();
        protected string _rootPath;
        protected string CurrentItem;

        protected TDemoExplorerViewCustomDataProviderSelection(string apath)
        {
            _rootPath = $@"{apath}" + (apath.EndsWith("\\") ? string.Empty : "\\");
            FillItems();
        }

        protected virtual void FillItems()
        {
            var dirs = Directory.GetDirectories(_rootPath, "*");
            if (dirs.Any())
            {
                _items.AddRange(dirs.Where(c =>
                {
                    var di = new DirectoryInfo(c);
                    return di.Attributes.HasFlag(FileAttributes.Directory)
                        && !di.Attributes.HasFlag(FileAttributes.System)
                        && !di.Attributes.HasFlag(FileAttributes.Hidden);
                }));
            }

            if (_items.Any())
            {
                CurrentItem = _items[_index];
            }
        }

        public override bool NextRow()
        {
            if (!_items.Any())
                return false;

            _index++;
            bool result = _index < _items.Count;

            if (result)
            {
                CurrentItem = _items[_index];
            }
            else
            {
                _index = 0;
            }

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
    }

    public class TDemoExplorerViewGroupingTreeDrivesProvider : TDemoExplorerViewAbstractDataProviderSelection
    {
        private DriveInfo _currentDrive;
        private DriveInfo[] _drivers;
        private int _index = 0;

        public TDemoExplorerViewGroupingTreeDrivesProvider()
        {
            _drivers = DriveInfo.GetDrives().Where(c => c.DriveType == DriveType.Fixed).ToArray();
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
    }

    public class TDemoExplorerViewDataProviderSelection : TDemoExplorerViewCustomDataProviderSelection
    {
        private const string _ext = "*.aiff;*.aif;*.ogg;*.oga;*.wav;*.mp3;*.mp2;*.mp1;*.mpga;*.umx;*.mod;*.mo3;*.it;*.s3m;*.mtm;*.xm;*.w64;*.cda;*.iso;*.dff;*.dsf;*.aac;*.m4a;*.m4b;*.mp4;*.ac3;*.ape;*.mac;*.flac;*.fla;*.midi;*.mid;*.rmi;*.kar;*.mpc;*.mp+;*.mpp;*.opus;*.spx;*.tta;*.wma;*.wv;*.tak;";
        private readonly string[] _fields;

        private readonly IEnumerable<string> _fileExtensions  = _ext.Split(new [] {';'}, StringSplitOptions.RemoveEmptyEntries)
            .Select(c => c.Replace("*", string.Empty));

        public TDemoExplorerViewDataProviderSelection(string apath, IEnumerable<string> fields) 
            : base(apath)
        {
            _fields = fields.ToArray();
        }

        protected override void FillItems()
        {
            _items = Directory.EnumerateFiles(_rootPath, "*.*", SearchOption.TopDirectoryOnly)
                .Where(c => _fileExtensions.Contains(Path.GetExtension(c))).ToList();

            if (!_items.Any())
                return;

            if (_index < _items.Count)
                CurrentItem = _items[_index];
        }

        public override double GetValueAsFloat(int fieldIndex)
        {
            if (string.IsNullOrWhiteSpace(CurrentItem))
                return 0;

            var fi = new FileInfo(CurrentItem);

            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileAccessTime))
            {
                return fi.LastAccessTime.ToOADate();
            }

            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileCreationTime))
            {
                return fi.CreationTime.ToOADate();
            }

            return 0;
        }

        public override long GetValueAsInt64(int fieldIndex)
        {
            if (string.IsNullOrWhiteSpace(CurrentItem))
                return 0;

            return new FileInfo(CurrentItem).Length;
        }

        public override string GetValueAsString(int fieldIndex)
        {
            if (string.IsNullOrWhiteSpace(CurrentItem))
            {
                return string.Empty;
            }

            var fi = new FileInfo(CurrentItem);
            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileName))
            {
                return $"myschema://{fi.FullName}";// fi.FullName;
            }

            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_FileFormat))
            {
                return Path.GetExtension(CurrentItem).Replace(".", string.Empty);
            }

            if (fieldIndex == GetIndex(DemoMusicLibrary.EVDS_ID))
            {
                return string.Empty;
            }

            return string.Empty;
        }

        private int GetIndex(string fieldName)
        {
            return Array.IndexOf(_fields.ToArray(), fieldName);
        }
    }
}