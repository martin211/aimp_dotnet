namespace AIMP.SDK.Services.Playback
{
    public delegate bool AimpCheckUrl(ref string url);

    public interface IExtensionPlayerHook
    {
         event AimpCheckUrl OnCheckURL;
    }
}