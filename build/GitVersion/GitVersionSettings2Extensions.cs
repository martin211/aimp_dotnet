// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using Nuke.Common.Tooling;

namespace Aimp.DotNet.Build
{
    public static class GitVersionSettings2Extensions
    {
        public static GitVersionSettings2 SetNoNormalize(this GitVersionSettings2 settings, bool value)
        {
            settings = settings.NewInstance();
            settings.NoNormalize = value;
            return settings;
        }
    }
}