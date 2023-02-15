//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.MessageDispatcher
{
    /// <summary>
    /// Message direction types.
    /// </summary>
    public enum MessageDirectionType
    {
        /// <summary>
        /// Get a property value.
        /// </summary>
        Get = 0,

        /// <summary>
        /// Set a property value.
        /// </summary>
        Set = 1
    }

    /// <summary>
    /// Provides an access to the messaging mechanism.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceMessageDispatcher : IAimpService
    {
        /// <summary>
        /// Sends the specified message.
        /// </summary>
        /// <param name="message">The message <see cref="AimpCoreMessageType" />.</param>
        /// <param name="param1">The message direction <see cref="MessageDirectionType" />.</param>
        /// <param name="param2">The param2.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Send(AimpCoreMessageType message, int param1, ref IntPtr param2);

        /// <summary>
        /// Registers the specified message.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <returns>System.Int32.</returns>
        int Register(string message);

        /// <summary>
        /// Setup the specified message hook.
        /// </summary>
        /// <param name="hook">The message hook.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Hook(IAimpMessageHook hook);

        /// <summary>
        /// Unhooks the specified hook.
        /// </summary>
        /// <param name="hook">The message hook.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Unhook(IAimpMessageHook hook);
    }
}
