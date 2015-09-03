using System;

namespace AIMP.SDK.Services.Player
{
    public delegate bool CheckUrl(string url);

    public interface IExtensionPlayerHook
    {
         event CheckUrl OnCheckURL;
    }
}