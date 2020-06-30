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
using System.Collections;
using System.Collections.Generic;
using System.Windows.Forms;
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

        public ActionResultType ConfigLoad(IAimpStream stream)
        {
            return ActionResultType.OK;
        }

        public ActionResultType ConfigSave(IAimpStream stream)
        {
            return ActionResultType.OK;
        }

        public ActionResultType ExecuteDialog(IntPtr ownerHandle)
        {
            MessageBox.Show("!!!");
            return ActionResultType.OK;
        }

        public void Initialize(IAimpPlaylistPreimageListener listener)
        {
            _manager = listener;
        }

        public void FinalizeObject()
        {
            _factory.Preimages.Remove(this);
        }

        public ActionResultType GetFiles(IAimpTaskOwner owner, out int preimageFlags, out IList dataList)
        {
            preimageFlags = (int)PreimageFlags.None;
            dataList = new List<string>
            {
                Environment.GetFolderPath(Environment.SpecialFolder.MyMusic)
            };

            return ActionResultType.OK;
        }

        ~TestPreimage()
        {
            FinalizeObject();
        }
    }
}