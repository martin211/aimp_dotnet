//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.MUIManager
{
    /// <summary>
    /// MUI manager.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    // ReSharper disable InconsistentNaming
    public interface IAimpServiceMUI : IAimpService
        // ReSharper restore InconsistentNaming
    {
        /// <summary>
        /// Gets the current locale name.
        /// </summary>
        /// <returns>System.String.</returns>
        string GetName();

        /// <summary>
        /// Gets the value.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>System.String.</returns>
        string GetValue(string key);

        /// <summary>
        /// Gets the value part.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="index">The index.</param>
        /// <returns>System.String.</returns>
        string GetValuePart(string key, int index);
    }
}
