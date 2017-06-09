using System;
using AIMP.SDK;
using AIMP.SDK.Threading;

namespace dotnet_threading
{
    public class TestTask : IAimpTask
    {
        public AimpActionResult Execute(IAimpTaskOwner owner)
        {
            if (!owner.IsCanceled)
            {
                System.Diagnostics.Debug.WriteLine("TestTask:\tExecute");
            }

            if (!owner.IsCanceled)
            {
                System.Threading.Thread.Sleep(TimeSpan.FromSeconds(10));
            }

            return AimpActionResult.Ok;
        }
    }
}
