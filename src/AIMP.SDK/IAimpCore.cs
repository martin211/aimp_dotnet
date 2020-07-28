// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Runtime.InteropServices;
using AIMP.SDK.MessageDispatcher;

namespace AIMP.SDK
{
    /// <summary>
    /// Delegate AimpEventsDelegate
    /// </summary>
    /// <param name="param1">The param1.</param>
    /// <param name="param2">The param2.</param>
    public delegate void AimpEventsDelegate(AimpCoreMessageType param1, int param2);

    /// <summary>
    /// This interface provides an ability to access to services and an ability to register custom services and extensions.
    /// </summary>
    public interface IAimpCore
    {
        /// <summary>
        /// Gets the path to one of the "system" folders of player.
        /// </summary>
        /// <param name="aimpCorePath">The aimp core path <seealso cref="AimpMessages.AimpCorePathType" /> type.</param>
        /// <returns>System.String.</returns>
        string GetPath(AimpCorePathType aimpCorePath);

        /// <summary>
        /// Sends the message.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="param">The parameter.</param>
        /// <param name="objectParameter">The object parameter.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SendMessage(AimpCoreMessageType message, int param, object objectParameter);

        /// <summary>
        /// Method provides an ability to register extension.
        /// An access to extensions provides by specified for it services.For example: IAimpServiceAudioDecoders.
        /// All extensions will be automatically unregistered from the application before plugin finalization.
        /// </summary>
        /// <param name="extension">The Aimp extension.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult RegisterExtension(IAimpExtension extension);

        /// <summary>
        /// Method provides an ability to unregister specified extension manually.
        /// Note 1: all extensions will be automatically unregistered from the application before plugin finalization.So, this method is optional.
        /// Note 2: extension may be used at the current time, in this case it will be completely unregistered only the after release
        /// </summary>
        /// <param name="extension">The Aimp extension.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult UnregisterExtension(IAimpExtension extension);

        /// <summary>
        /// Creates the Aimp stream instance.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
        [Obsolete("Use CreateObject instead it")]
        AimpActionResult<IAimpStream> CreateStream();

        /// <summary>
        /// Creates the object.
        /// </summary>
        /// <typeparam name="TAimpObject">The type of the t aimp object.</typeparam>
        /// <returns>AimpActionResult&lt;IAimpObject&gt;.</returns>
        AimpActionResult<IAimpObject> CreateObject<TAimpObject>() where TAimpObject : IAimpObject;
    }
}