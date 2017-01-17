namespace AIMP.SDK.Playback
{
    public delegate bool AimpCheckUrl(ref string url);

    public interface IAimpExtensionPlayerHook
    {
         event AimpCheckUrl OnCheckURL;
    }
}