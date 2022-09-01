//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Collections;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.Objects;
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

        public string FactoryId => _factory.GetId().Result;

        public bool AutoSync { get; set; }

        public bool AutoSyncOnStartup { get; set; }

        public bool HasDialog => true;

        public string SortTemplate => string.Empty;

        public AimpActionResult ConfigLoad(IAimpStream stream)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult ConfigSave(IAimpStream stream)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult ExecuteDialog(IntPtr ownerHandle)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public void Initialize(IAimpPlaylistPreimageListener listener)
        {
        }

        public void FinalizeObject()
        {
        }

        public AimpActionResult<IAimpDataFilter> GetFilter()
        {
            return new AimpActionResult<IAimpDataFilter>(ActionResultType.OK, null);
        }

        public AimpActionResult<IAimpDataStorage> GetStorage()
        {
            return new AimpActionResult<IAimpDataStorage>(ActionResultType.OK, null);
        }

        public AimpActionResult<int, IList> GetFiles(IAimpTaskOwner owner)
        {
            IList dataList = new List<string>
            {
                Environment.GetFolderPath(Environment.SpecialFolder.MyMusic)
            };
            return new AimpActionResult<int, IList>(ActionResultType.OK, 0, dataList);
        }
    }
}
