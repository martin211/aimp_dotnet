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
using Nuke.Common.Tools.GitVersion;

namespace Aimp.DotNet.Build
{
    public class GitVersionSettings2 : GitVersionSettings
    {
        public virtual bool NoNormalize { get; internal set; }

        protected override Arguments ConfigureArguments(Arguments arguments)
        {
            var args = base.ConfigureArguments(arguments);
            if (NoNormalize)
            {
                args.Add("/nonormalize");
            }

            return args;
        }
    }
}