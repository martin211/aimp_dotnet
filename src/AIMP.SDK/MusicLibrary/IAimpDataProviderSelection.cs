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
    /// Interface provides access to the currently selected data at DataProvider.
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpDataProviderSelection
    {
        double GetValueAsFloat(int fieldIndex);

        int GetValueAsInt32(int fieldIndex);

        long GetValueAsInt64(int fieldIndex);

        string GetValueAsString(int fieldIndex);

        /// <summary>
        /// Return the True value to notify the Music library the page-by-page access method is used to access to the data. 
        /// Value specifies that next page of data is available. 
        /// Note that this mode automatically disable for end users the Group Details and the Album Thumbnails views.
        /// </summary>
        bool HasNextPage();

        /// <summary>
        /// Jumps to next row. Returns False if current row is last.
        /// </summary>
        bool NextRow();
    }
}