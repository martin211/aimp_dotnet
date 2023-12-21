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
    /// The IAimpMessageHook interface provides an ability to hook all messages that processes via
    /// <see cref="IAimpServiceMessageDispatcher" />.
    /// Note that you must remove hook manually in the <see cref="IAimpPlugin.Dispose" />.
    /// </summary>
    public interface IAimpMessageHook
    {
        /// <summary>
        /// Occurs when plugin receive message from player.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="param1">The param1.</param>
        /// <param name="param2">The param2. See official SDK documentation to get more info about output parameter.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult CoreMessage(AimpCoreMessageType message, int param1, IntPtr param2);
    }
}
