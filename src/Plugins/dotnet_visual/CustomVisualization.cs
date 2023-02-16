//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Diagnostics;
using AIMP.SDK.Visuals;

namespace dotnet_visual
{
    public class CustomVisualization : IAimpExtensionCustomVisualization
    {
        public AimpVisualFlags GetFlags()
        {
            return AimpVisualFlags.NotSuspend & AimpVisualFlags.RQDDataSpectrum & AimpVisualFlags.RQDDataWaveForm;
        }

        public void Draw(AimpVisualData data)
        {
            Debug.WriteLine("CustomVisualization:\tDraw");
        }
    }
}
