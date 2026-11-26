namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// Constants from apiMusicLibrary.h.
    /// </summary>
    public static class AimpMlPropId
    {
        public const int DataStorageId = 0;
        public const int DataStorageCaption = 1;
        public const int DataStorageCapabilities = 2;
        public const int DataStorageGroupingPreset = 20;

        public const int FieldCustom = 0;
        public const int FieldName = 1;
        public const int FieldType = 2;
        public const int FieldFlags = 3;
        public const int FieldImage = 4;
        public const int FieldDisplayValue = 5;

        public const int FieldFilterField = 1;
        public const int FieldFilterOperation = 2;
        public const int FieldFilterValue1 = 3;
        public const int FieldFilterValue2 = 4;

        public const int FieldFilterByArrayField = 1;

        public const int FilterGroupOperation = 1;

        public const int FilterLimit = 11;
        public const int FilterOffset = 12;
        public const int FilterSortByList = 15;
        public const int FilterSearchString = 20;
        public const int FilterAlphabeticIndex = 21;

        public const int GroupingPresetCustom = 0;
        public const int GroupingPresetId = 1;
        public const int GroupingPresetName = 2;
        public const int GroupingPresetStandardFields = 10;
    }
}