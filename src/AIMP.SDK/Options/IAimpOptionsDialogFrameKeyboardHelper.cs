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
    /// Interface IAimpOptionsDialogFrameKeyboardHelper
    /// </summary>
    public interface IAimpOptionsDialogFrameKeyboardHelper
    {
        /// <summary>
        /// Dialogs the key.
        /// </summary>
        /// <param name="charCode">The character code.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        bool DialogKey(int charCode);

        /// <summary>
        /// Selects the first control.
        /// </summary>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        bool SelectFirstControl();

        /// <summary>
        /// Selects the next control.
        /// </summary>
        /// <param name="findForward">The find forward.</param>
        /// <param name="isTabKeyAction">The is tab key action.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        bool SelectNextControl(int findForward, int isTabKeyAction);
    }
}