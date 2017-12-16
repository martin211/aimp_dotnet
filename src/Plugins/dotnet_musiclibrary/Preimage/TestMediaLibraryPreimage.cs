using System;
using System.Collections;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.Playlist;
using AIMP.SDK.Threading;

namespace AIMP.DotNet.MusicLibrary.Preimage
{
    public class TestMediaLibraryPreimage : IAimpPlaylistPreimageDataProvider, IAimpMusicLibraryPlaylistPreimage
    {
        private readonly MediaLibraryPreimageFactory _factory;

        public TestMediaLibraryPreimage(MediaLibraryPreimageFactory factory)
        {
            _factory = factory;
            _factory.Preimages.Add(this);
            AutoSync = true;
            AutoSyncOnStartup = true;
        }

        public AimpActionResult GetFiles(IAimpTaskOwner owner, out int preimageFlags, out IList dataList)
        {
            preimageFlags = 0;
            dataList = new List<string>
            {
                Environment.GetFolderPath(Environment.SpecialFolder.MyMusic)
            };

            return AimpActionResult.Ok;
        }

        public string FactoryId
        {
            get
            {
                string id;
                _factory.GetId(out id);
                return id;
            }
        }

        public bool AutoSync { get; set; }

        public bool AutoSyncOnStartup { get; set; }

        public bool HasDialog => true;

        public string SortTemplate => string.Empty;

        public AimpActionResult ConfigLoad(IAimpStream stream)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult ConfigSave(IAimpStream stream)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult ExecuteDialog(IntPtr ownerHandle)
        {
            return AimpActionResult.Ok;
        }

        public void Initialize(IAimpPlaylistPreimageListener listener)
        {
            
        }

        public void FinalizeObject()
        {
            
        }

        public AimpActionResult GetFilter(out IAimpDataFieldFilter filter)
        {
            filter = null;
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetStorage(out IAimpDataStorage storage)
        {
            storage = null;
            return AimpActionResult.Ok;
        }
    }
}