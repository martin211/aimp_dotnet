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
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Objects;
using AIMP.SDK.Playlist;
using AIMP.SDK.Playlist.Objects;
using AIMP.SDK.Threading;

namespace Aimp.DotNet.SmartPlaylist
{
    public class TestPreimage : IAimpPlaylistPreimageDataProvider, IAimpPlaylistPreimage
    {
        private readonly TestPreimageFactory _factory;
        private IAimpPlaylistPreimageListener _manager;

        public TestPreimage(TestPreimageFactory factory)
        {
            _factory = factory;
            _factory.Preimages.Add(this);
            AutoSync = true;
        }

        public string FactoryId
        {
            get
            {
                var r = _factory.GetId();
                return r.Result;
            }
        }

        public bool AutoSync { get; set; }

        public bool AutoSyncOnStartup { get; set; }

        public bool HasDialog => true;

        public string SortTemplate => string.Empty;

        AimpActionResult IAimpPlaylistPreimage.ConfigLoad(IAimpStream stream)
        {
            return ConfigLoad(stream);
        }

        public AimpActionResult ConfigSave(IAimpStream stream)
        {
            throw new NotImplementedException();
        }

        AimpActionResult IAimpPlaylistPreimage.ExecuteDialog(IntPtr ownerHandle)
        {
            return ExecuteDialog(ownerHandle);
        }

        AimpActionResult ExecuteDialog(IntPtr ownerHandle)
        {
            MessageBox.Show("!!!");
            return new AimpActionResult(ActionResultType.OK);
        }

        AimpActionResult ConfigLoad(IAimpStream stream)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public void Initialize(IAimpPlaylistPreimageListener listener)
        {
            _manager = listener;
        }

        public void FinalizeObject()
        {
            _factory.Preimages.Remove(this);
        }

        ~TestPreimage()
        {
            FinalizeObject();
        }

        public AimpActionResult<int, IList> GetFiles(IAimpTaskOwner owner)
        {
            return new AimpActionResult<int, IList>(ActionResultType.OK, (int) PreimageFlags.None, new List<string>
            {
                Environment.GetFolderPath(Environment.SpecialFolder.MyMusic)
            });
        }
    }
}
