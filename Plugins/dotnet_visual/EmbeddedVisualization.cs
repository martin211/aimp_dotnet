using System;
using System.Diagnostics;
using AIMP.SDK;
using AIMP.SDK.Visuals;

namespace dotnet_visual
{
    using System.Drawing;

    public class EmbeddedVisualization : IAimpExtensionEmbeddedVisualization
    {
        public void Click(int x, int y, AimpVisualClickButtonType button)
        {
            Debug.WriteLine("Click");
        }

        public void Resize(int newWidth, int newHeight)
        {
            Debug.WriteLine("Resize");
        }

        public AimpVisualFlags GetFlags()
        {
            Debug.WriteLine("GetFlag");
            return AimpVisualFlags.AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM;
        }

        public AimpActionResult GetMaxDisplaySize(out int width, out int height)
        {
            Debug.WriteLine("GetMaxDisplaySize");
            width = 100;
            height = 100;
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetName(out string name)
        {
            Debug.WriteLine("GetName");
            name = "Test Visualization";
            return AimpActionResult.Ok;
        }

        public AimpActionResult Initialize(int width, int height)
        {
            Debug.WriteLine("Initialize");
            return AimpActionResult.Ok;
        }

        public void OnFinalize()
        {
            Debug.WriteLine("Finalize");
        }

        public void Draw(IntPtr dc, AimpVisualData data)
        {
            var g = Graphics.FromHdc(dc);
            g.DrawRectangle(new Pen(Color.Crimson), 0,0, 20, 20);
        }
    }
}