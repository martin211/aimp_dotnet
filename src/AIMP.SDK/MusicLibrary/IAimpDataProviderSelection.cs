namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Interface provides access to the currently selected data at DataProvider.
    /// </summary>
    public interface IAimpDataProviderSelection
    {
        double GetValueAsFloat(int fieldIndex);

        int GetValueAsInt32(int fieldIndex);

        long GetValueAsInt64(int fieldIndex);

        string GetValueAsString(int fieldIndex);

        bool HasNextPage();

        bool NextRow();
    }
}