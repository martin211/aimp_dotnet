using System;
using AIMP.SDK;
using AIMP.SDK.Threading;

namespace dotnet_threading
{
    [AimpPlugin("ThreadinDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "Threading demo plugin")]
    public class ThreadingPlugin : AimpPlugin
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