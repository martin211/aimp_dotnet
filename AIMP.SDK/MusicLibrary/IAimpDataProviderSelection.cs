namespace AIMP.SDK.MusicLibrary
{
    public interface IAimpDataProviderSelection
    {
        double GetValueAsFloat(int fieldIndex);

        int GetValueAsInt32(int fieldIndex);

        long GetValueAsInt64(int fieldIndex);

        string GetValueAsString(int fieldIndex);

        AimpActionResult HasNextPage();

        bool NextRow();
    }
}