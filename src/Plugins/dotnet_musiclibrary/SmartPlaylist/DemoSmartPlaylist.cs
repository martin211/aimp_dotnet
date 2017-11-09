// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using AIMP.SDK.Threading;

namespace AIMP.DotNet.MusicLibrary.SmartPlaylist
{
    public class DemoSmartPlaylist : IAimpPlaylistPreimageDataProvider, IAimpPlaylistPreimage
    {
        public AimpActionResult GetFiles(IAimpTaskOwner owner, PreimageFlags preimageFlags, IAimpObjectList<object> dataList)
        {
            System.Diagnostics.Debugger.Break();
            return AimpActionResult.Ok;
        }

        public string FactoryId => "Demo.PreimageFactory";

        public bool AutoSync
        {
            get { return false; }
            set {}
        }

        public bool AutoSyncOnStartup { get; set; }

        public bool HasDialog => false;

        public string SortTemplate { get; }

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
            return AimpActionResult.NotImplemented;
        }

        public void Initialize(IAimpPlaylistPreimageListener listener)
        {
            System.Diagnostics.Debug.WriteLine("DemoSmartPlaylist.Initialize");
        }

        public void FinalizeObject()
        {
            System.Diagnostics.Debug.WriteLine("DemoSmartPlaylist.Dispose");
        }
        
    }
}