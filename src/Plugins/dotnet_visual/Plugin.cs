﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP;
using AIMP.SDK;
using AIMP.SDK.Visuals;

namespace dotnet_visual
{
    [AimpPlugin("dotnet_visual", "Evgeniy Bogdan", AdditionalInfo.Version, AimpPluginType = AimpPluginType.Visuals)]
    public class Plugin : AimpPlugin
    {
        private IAimpExtensionCustomVisualization _customVisualization;
        private IAimpExtensionEmbeddedVisualization _embeddedVisualization;

        public override void Initialize()
        {
            _embeddedVisualization = new EmbeddedVisualization();
            //_customVisualization = new CustomVisualization();

            Player.Core.RegisterExtension(_embeddedVisualization);
        }

        public override void Dispose()
        {
            Player.Core.UnregisterExtension(_embeddedVisualization);
        }
    }
}
