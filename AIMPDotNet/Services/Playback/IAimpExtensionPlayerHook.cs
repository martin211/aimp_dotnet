namespace AIMP.SDK.Services.Playback
{
    public delegate bool AimpCheckUrl(ref string url);

    public interface IAimpExtensionPlayerHook
    {
         event AimpCheckUrl OnCheckURL;
    }
}