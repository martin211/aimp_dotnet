// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Options
{
    using System;

    /// <summary>
    /// 
    /// </summary>
    public interface IAimpOptionsDialogFrame : IAimpExtension
    {
        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <returns></returns>
        string GetName();

        /// <summary>
        /// Creates the frame.
        /// </summary>
        /// <param name="parentWindow">The parent window.</param>
        /// <returns></returns>
        IntPtr CreateFrame(IntPtr parentWindow);

        /// <summary>
        /// Destroys the frame.
        /// </summary>
        void DestroyFrame();

        /// <summary>
        /// Occurs when [notification].
        /// </summary>
        void Notification(int id);
    }
}