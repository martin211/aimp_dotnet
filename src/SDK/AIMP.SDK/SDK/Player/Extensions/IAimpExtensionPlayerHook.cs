namespace AIMP.SDK.Player.Extensions;

/// <summary>
/// Interface IAimpExtensionPlayerHook
/// Implements the <see cref="AIMP.SDK.IAimpExtension" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpExtension" />
public interface IAimpExtensionPlayerHook : IAimpExtension
{
    /// <summary>
    /// Called when [check URL].
    /// </summary>
    /// <param name="url">The URL.</param>
    /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
    bool OnCheckURL(ref string url);
}