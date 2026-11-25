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