using AIMP.SDK;
using AIMP.SDK.Visuals;

namespace dotnet_visual
{
    [AimpPlugin("dotnet_visual", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Visuals)]
    public class AimpVisualPlugin : AimpPlugin
    {
        private IAimpExtensionEmbeddedVisualization _embeddedVisualization;

        public override void Initialize()
        {
            _embeddedVisualization = new EmbeddedVisualization();

            Player.Core.RegisterExtension(_embeddedVisualization);
        }

        public override void Dispose()
        {
            Player.Core.UnregisterExtension(_embeddedVisualization);
        }
    }
}
