namespace AIMP.SDK.Interfaces
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
        /// Gets the path.
        /// </summary>
        /// <param name="aimpCorePath">The aimp core path <seealso cref="AimpMessages.AimpCorePathType"/> type.</param>
        /// <returns></returns>
        string GetPath(AimpMessages.AimpCorePathType aimpCorePath);

        /// <summary>
        /// Occurs when [core message].
        /// </summary>
        event AimpEventsDelegate CoreMessage;
    }
}