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

namespace AIMP.SDK.Options
{
    /// <summary>
    ///     Interface IAimpServiceOptionsDialog
    ///     Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceOptionsDialog : IAimpService
    {
        /// <summary>
        ///     Frames the modified.
        /// </summary>
        /// <param name="frame">The frame.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult FrameModified(IAimpOptionsDialogFrame frame);

        /// <summary>
        ///     Frames the show.
        /// </summary>
        /// <param name="frame">The frame.</param>
        /// <param name="forceShow">if set to <c>true</c> [force show].</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult FrameShow(IAimpOptionsDialogFrame frame, bool forceShow);
    }
}