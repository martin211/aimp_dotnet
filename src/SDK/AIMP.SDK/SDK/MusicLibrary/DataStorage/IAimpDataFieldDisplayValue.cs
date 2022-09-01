//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Providers an ability to customize display value for specified field.
    /// </summary>
    public interface IAimpDataFieldDisplayValue
    {
        /// <summary>
        /// Gets the display value.
        /// </summary>
        /// <param name="value">The original value.</param>
        /// <param name="length">Count of characters in result.</param>
        /// <returns>System.String.</returns>
        string GetDisplayValue(object value, out int length);
    }
}
