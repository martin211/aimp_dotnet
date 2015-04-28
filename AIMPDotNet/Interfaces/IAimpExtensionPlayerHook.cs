using System;

namespace AIMP.SDK.Interfaces
{
    public interface IAimpExtensionPlayerHook
    {
        event EventHandler OnCheckUrl;
    }
}