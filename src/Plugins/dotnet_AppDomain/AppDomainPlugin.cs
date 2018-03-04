using System;
using AIMP.SDK;

namespace AIMP.DotNet.AppDomainPlugin
{
    [AimpPlugin("dotnet_AppDomainDemo", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons, RequireAppDomain = true)]
    public class AppDomainPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            System.Diagnostics.Debug.WriteLine(AppDomain.CurrentDomain.BaseDirectory);
            System.Diagnostics.Debug.WriteLine(AppDomain.CurrentDomain.Id);
        }

        public override void Dispose()
        {
            
        }
    }
}
