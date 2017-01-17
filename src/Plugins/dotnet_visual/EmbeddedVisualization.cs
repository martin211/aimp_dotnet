﻿using System;
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

            //Форма волны
            int Width = 100;
            int Height = 45;
            int offset = Height / 2;
            int y = 0;
            int z = 0;
            Bitmap bmp = new Bitmap(Width, Height);

            for (int ci = 0; ci < 2; ci++)
            {
                for (int x = 0; x < Width - 1; x++)
                {
                    z = (int)((1 - data.WaveForm[ci][x]) * offset / 2);
                    if (z < 0) z = 0;
                    if (z > Height) z = Height - 1;
                    if (x == 0) y = z;

                    do // draw line from previous sample...
                    {
                        if (y < z)
                        { y += 1; }
                        else if (y > z)
                        { y -= 1; }

                        if (ci == 0)
                        {
                            bmp.SetPixel(x, y + 11, Color.Yellow);
                        }

                        if (ci == 1)
                        {
                            bmp.SetPixel(x, y + 11, Color.Pink);
                        }
                    } while (y != z);
                }
            }

            //Очистим окно визуализации
            g.Clear(Color.Black);
            g.DrawImage(bmp, 0, 0, Width, Height);
        }
    }
}