// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK;

namespace Aimp.TestRunner.UnitTests;

public class AimpTestContext : MarshalByRefObject
{
    private static AimpTestContext _instance;
    public static AimpTestContext Instance => _instance ?? (_instance = new AimpTestContext());

    public IAimpPlayer AimpPlayer { get; set; }
}
