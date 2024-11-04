//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.Extension.Command;

/// <summary>
/// Represents a find result.
/// </summary>
public class FindResult
{
    /// <summary>
    /// ID of grouping tree preset that must be selected to apply the GroupingTreeSelection.
    /// Return the nil/null if file can be located using current grouping tree preset.
    /// </summary>
    public IAimpString GroupingPresetID { get; set; }

    /// <summary>
    /// Path to grouping tree node that contains the file.
    /// Return the nil/null or empty selection to select root of grouping tree.
    /// </summary>
    public IAimpGroupingTreeSelection GroupingTreeSelection { get; set; }
}

/// <summary>
/// Command helps player to find file specified by user in music library.
/// If the file contains in plugin's data storage, plugin must initialize output parameters and return <see cref="ActionResultType.OK"/> as result of following method. 
/// </summary>
public interface IAimpDataStorageCommandFindInLibrary
{
    AimpActionResult<FindResult> Find(IAimpFileInfo fileInfo);
}