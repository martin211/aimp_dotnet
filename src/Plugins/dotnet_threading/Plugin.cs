//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK;

namespace dotnet_threading
{
    [AimpPlugin("ThreadinDemoPlugin", "Evgeniy Bogdan", AdditionalInfo.Version, AimpPluginType = AimpPluginType.Addons, FullDescription = "Threading demo plugin")]
    public class Plugin : AimpPlugin
    {
        public override void Initialize()
        {
            var task = new TestTask();
            UIntPtr taskThread;

            //Player.ServiceThreadPool.Execute(task, out taskThread);

            var task2 = new TestTask();
            Player.ServiceSynchronizer.ExecuteInMainThread(task2, true);
        }

        public override void Dispose()
        {
        }
    }
}
