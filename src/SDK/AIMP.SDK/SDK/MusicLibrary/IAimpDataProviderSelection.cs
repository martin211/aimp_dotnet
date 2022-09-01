//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Interface provides access to the currently selected data at DataProvider.
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpDataProviderSelection
    {
        /// <summary>
        /// Gets the value as float.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.Double.</returns>
        double GetValueAsFloat(int fieldIndex);

        /// <summary>
        /// Gets the value as int32.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.Int32.</returns>
        int GetValueAsInt32(int fieldIndex);

        /// <summary>
        /// Gets the value as int64.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.Int64.</returns>
        long GetValueAsInt64(int fieldIndex);

        /// <summary>
        /// Gets the value as string.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.String.</returns>
        string GetValueAsString(int fieldIndex);

        /// <summary>
        /// Jumps to next row. Returns False if current row is last.
        /// </summary>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        bool NextRow();
    }
}
