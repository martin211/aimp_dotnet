namespace AIMP.SDK.Services.Playback
{
    public delegate bool AimpCheckUrl(string url);

    public interface IExtensionPlayerHook
    {
         event AimpCheckUrl OnCheckURL;
    }
}