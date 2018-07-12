using System;
using System.Diagnostics;

namespace AIMP.SDK.MessageDispatcher
{
    public interface IAimpMessageHook
    {
        AimpActionResult CoreMessage(AimpMessages.AimpCoreMessageType message, int param1, int param2);
    }
}