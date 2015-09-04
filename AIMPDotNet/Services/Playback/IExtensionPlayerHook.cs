namespace AIMP.SDK.Services.PlaybackManager
{
    public delegate bool AimpCheckUrl(string url);

    public interface IExtensionPlayerHook
    {
         event AimpCheckUrl OnCheckURL;
    }
}