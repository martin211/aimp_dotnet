//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Reflection;
using NUnit.Engine.Extensibility;

[assembly:
    ExtensionPoint("/NUnit/Engine/TypeExtensions/IDriverFactory", typeof(IDriverFactory),
        Description = "Driver for NUnit tests using AIMP.")]

namespace Aimp.TestRunner.Engine;

[Extension]
public class AimpNUnitFrameworkDriver : IDriverFactory
{
    private const string NUNIT_FRAMEWORK = "nunit.framework";


    public bool IsSupportedTestFramework(AssemblyName reference)
    {
        return NUNIT_FRAMEWORK.Equals(reference.Name, StringComparison.OrdinalIgnoreCase) &&
               reference.Version.Major == 4;
    }

    public IFrameworkDriver GetDriver(AppDomain domain, AssemblyName reference)
    {
        return new AimpNUnit3FrameworkDriver(domain, reference);
    }
}
