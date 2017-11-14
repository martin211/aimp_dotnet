using System;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;
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

        ~TestPreimage()
        {
            FinalizeObject();
        }

        public AimpActionResult GetFiles(IAimpTaskOwner owner, out PreimageFlags preimageFlags, out IList<object> dataList)
        {
            preimageFlags = PreimageFlags.None;
            dataList = new List<object>
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
            _manager = listener;
        }

        public void FinalizeObject()
        {
            _factory.Preimages.Remove(this);
        }
    }
}