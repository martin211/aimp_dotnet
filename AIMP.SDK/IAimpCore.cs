namespace AIMP.SDK
{
    /// <summary>
    /// 
    /// </summary>
    public delegate void AimpEventsDelegate(AimpMessages.AimpCoreMessageType param1, int param2);

    /// <summary>
    /// AIMP Core interface.
    /// </summary>
    public interface IAimpCore
    {
        /// <summary>
        /// Gets the specified path.
        /// </summary>
        /// <param name="aimpCorePath">The aimp core path <seealso cref="AimpMessages.AimpCorePathType"/> type.</param>
        /// <returns></returns>
        string GetPath(AimpMessages.AimpCorePathType aimpCorePath);

        /// <summary>
        /// Sends the message.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="param">The parameter.</param>
        /// <param name="objectParameter">The object parameter.</param>
        AimpActionResult SendMessage(AimpMessages.AimpCoreMessageType message, int param, object objectParameter);

        /// <summary>
        /// Registers the extension.
        /// </summary>
        /// <param name="extension">The extension.</param>
        AimpActionResult RegisterExtension(IAimpExtension extension);

        /// <summary>
        /// Unregisters the extension.
        /// </summary>
        /// <param name="extension">The extension.</param>
        AimpActionResult UnregisterExtension(IAimpExtension extension);

        /// <summary>
        /// Occurs when [core message].
        /// </summary>
        event AimpEventsDelegate CoreMessage;
    }
}