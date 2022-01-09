﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK.Threading;

namespace dotnet_threading
{
    public class TestTask : IAimpTask
    {
        public void Execute(IAimpTaskOwner owner)
        {
            if (!owner.IsCanceled)
            {
                System.Diagnostics.Debug.WriteLine("TestTask:\tExecute");
            }

            if (!owner.IsCanceled)
            {
                System.Threading.Thread.Sleep(TimeSpan.FromSeconds(10));
            }
        }
    }
}
