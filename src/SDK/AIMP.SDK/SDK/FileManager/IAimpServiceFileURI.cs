//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager;

public enum FileUriFlag
{
    /// <summary>
    /// Double extensions will be replaced with NewExt. If flag is not set - only last extension will be replaced.
    /// </summary>
    DoubleExt,

    /// <summary>
    /// if flag is set - function will change the extension of sub track instead of container's file name.
    /// </summary>
    PartExt
}

/// <summary>
/// The IAimpServiceFileURI service provides few methods to work with FileURI of real and virtual files.
/// </summary>
public interface IAimpServiceFileURI
{
    /// <summary>
    /// Method builds a FileURI based on file name of file-container and part name. Refer to the virtual files article.
    /// </summary>
    /// <param name="containerName">Name of the container.</param>
    /// <param name="partName">Name of the part.</param>
    /// <returns></returns>
    AimpActionResult<string> Build(string containerName, string partName);

    /// <summary>
    /// Methods parses the FileURI and returns file name of container and name of sub-track.
    /// If the FileURI related to real file - PartName will be set to nil/null 
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <returns></returns>
    AimpActionResult<Tuple<string, string>> Parse(string fileUri);

    /// <summary>
    /// Method provides an ability to change file ext of file container or sub track.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <param name="extension">New file extension in following format: .mp3</param>
    /// <param name="flag">The flag.</param>
    /// <returns></returns>
    AimpActionResult ChangeFileExt(string fileUri, string extension, FileUriFlag flag);

    /// <summary>
    /// Method provides an ability to extract file extension.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <param name="flag">The flag.</param>
    /// <returns></returns>
    AimpActionResult<string> ExtractFileExt(string fileUri, FileUriFlag flag);

    /// <summary>
    /// Method provides an ability to extract file name without the path.
    /// File name includes name of file-container and sub track name.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <returns></returns>
    AimpActionResult<string> ExtractFileName(string fileUri);

    /// <summary>
    /// Method provides an ability to get name of parent folder for real or virtual file.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <returns></returns>
    AimpActionResult<string> ExtractFileParentDirName(string fileUri);

    /// <summary>
    /// Method provides an ability to get name of parent:
    /// Function will return name of file-container if FileURI is related to virtual file.
    /// Function will return name of parent folder if FileURI is related to real file.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <returns></returns>
    AimpActionResult<string> ExtractFileParentName(string fileUri);

    /// <summary>
    /// Method provides an ability get path of file.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <returns></returns>
    AimpActionResult<string> ExtractFilePath(string fileUri);

    /// <summary>
    /// Method checks if FileURI is URL.
    /// </summary>
    /// <param name="fileUri">The file URI.</param>
    /// <returns></returns>
    AimpActionResult IsURL(string fileUri);
}