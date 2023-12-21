//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Reflection;

[assembly: AssemblyVersion(AIMP.SDK.AdditionalInfo.Version)]
[assembly: AssemblyFileVersion(AIMP.SDK.AdditionalInfo.Version)]
[assembly: AssemblyInformationalVersion("")]

[assembly: AssemblyCompany("")]
[assembly: AssemblyCopyright("Copyright © Evgeniy Bogdan 2023")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]

namespace AIMP.SDK
{
    internal static class AdditionalInfo
    {
        public const string Version = "1.0.0.0";
    }
}
