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

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    ///     Interface provides access to the currently selected data at DataProvider.
    ///     Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpDataProviderSelection
    {
        /// <summary>
        ///     Gets the value as float.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.Double.</returns>
        double GetValueAsFloat(int fieldIndex);

        /// <summary>
        ///     Gets the value as int32.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.Int32.</returns>
        int GetValueAsInt32(int fieldIndex);

        /// <summary>
        ///     Gets the value as int64.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.Int64.</returns>
        long GetValueAsInt64(int fieldIndex);

        /// <summary>
        ///     Gets the value as string.
        /// </summary>
        /// <param name="fieldIndex">Index of the field.</param>
        /// <returns>System.String.</returns>
        string GetValueAsString(int fieldIndex);

        /// <summary>
        ///     Return the True value to notify the Music library the page-by-page access method is used to access to the data.
        ///     Value specifies that next page of data is available.
        ///     Note that this mode automatically disable for end users the Group Details and the Album Thumbnails views.
        /// </summary>
        /// <returns><c>true</c> if [has next page]; otherwise, <c>false</c>.</returns>
        bool HasNextPage();

        /// <summary>
        ///     Jumps to next row. Returns False if current row is last.
        /// </summary>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        bool NextRow();
    }
}