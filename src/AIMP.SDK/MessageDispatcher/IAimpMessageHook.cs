// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System;
using System.Diagnostics;

namespace AIMP.SDK.MessageDispatcher
{
    public interface IAimpMessageHook
    {
        AimpActionResult CoreMessage(AimpMessages.AimpCoreMessageType message, int param1, int param2);
    }
}