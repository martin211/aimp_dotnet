using System;

namespace AIMP.SDK.Visuals
{
    public enum AimpVisualFlags
    {
        AIMP_VISUAL_FLAGS_RQD_DATA_WAVE,
        AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM,
        AIMP_VISUAL_FLAGS_NOT_SUSPEND
    }

    public interface IAimpExtensionEmbeddedVisualization
    {
        event EventHandler Click;

        AimpVisualFlags GetFlags();

        AimpActionResult GetMaxDisplaySize(out int width, out int height);

        AimpActionResult GetName(out string name);

        AimpActionResult Initialize(int width, int height);

        void Finalize();

        void Draw(IntPtr dc, AimpVisualData data);

        void Resize(int width, int height);
    }
}