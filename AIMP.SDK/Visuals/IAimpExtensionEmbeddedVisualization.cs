using System;

namespace AIMP.SDK.Visuals
{
    public enum AimpVisualClickButtonType
    {
        AIMP_VISUAL_CLICK_BUTTON_LEFT,
        AIMP_VISUAL_CLICK_BUTTON_MIDDLE
    }

    public interface IAimpExtensionEmbeddedVisualization : IAimpExtension
    {
        void Click(int x, int y, AimpVisualClickButtonType button);

        void Resize(int newWidth, int newHeight);

        AimpVisualFlags GetFlags();

        AimpActionResult GetMaxDisplaySize(out Int32 width, out Int32 height);

        AimpActionResult GetName(out string name);

        AimpActionResult Initialize(int width, int height);

        void OnFinalize();

        void Draw(IntPtr dc, AimpVisualData data);
    }
}