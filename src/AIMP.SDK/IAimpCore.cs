namespace AIMP.SDK
{
    /// <summary>
    /// 
    /// </summary>
    public delegate void AimpEventsDelegate(AimpMessages.AimpCoreMessageType param1, int param2);

    /// <summary>
    /// This interface provides an ability to access to services and an ability to register custom services and extensions.
    /// </summary>
    public interface IAimpCore
    {
        /// <summary>
        /// Gets the path to one of the "system" folders of player.
        /// </summary>
        /// <param name="aimpCorePath">The aimp core path <seealso cref="AimpMessages.AimpCorePathType"/> type.</param>
        string GetPath(AimpMessages.AimpCorePathType aimpCorePath);

        /// <summary>
        /// Sends the message.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="param">The parameter.</param>
        /// <param name="objectParameter">The object parameter.</param>
        AimpActionResult SendMessage(AimpMessages.AimpCoreMessageType message, int param, object objectParameter);

        /// <summary>
        /// Method provides an ability to register extension.
        /// An access to extensions provides by specified for it services.For example: IAimpServiceAudioDecoders.
        /// All extensions will be automatically unregistered from the application before plugin finalization.
        /// </summary>
        /// <param name="extension">The Aimp extension.</param>
        AimpActionResult RegisterExtension(IAimpExtension extension);

        /// <summary>
        /// Method provides an ability to unregister specified extension manually.
        /// Note 1: all extensions will be automatically unregistered from the application before plugin finalization.So, this method is optional.
        /// Note 2: extension may be used at the current time, in this case it will be completely unregistered only the after release
        /// </summary>
        /// <param name="extension">The Aimp extension.</param>
        AimpActionResult UnregisterExtension(IAimpExtension extension);

        /// <summary>
        /// Occurs when [core message].
        /// </summary>
        event AimpEventsDelegate CoreMessage;

        /// <summary>
        /// Creates the Aimp stream instance.
        /// </summary>
        /// <returns></returns>
        IAimpStream CreateStream();
    }
}