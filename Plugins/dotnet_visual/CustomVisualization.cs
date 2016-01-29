using System.Diagnostics;
using AIMP.SDK.Visuals;

namespace dotnet_visual
{
    public class CustomVisualization : IAimpExtensionCustomVisualization
    {
        public AimpVisualFlags GetFlags()
        {
            return AimpVisualFlags.AIMP_VISUAL_FLAGS_NOT_SUSPEND & AimpVisualFlags.AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM & AimpVisualFlags.AIMP_VISUAL_FLAGS_RQD_DATA_WAVE;
        }

        public void Draw(AimpVisualData data)
        {
            Debug.WriteLine("CustomVisualization:\tDraw");
        }
    }
}