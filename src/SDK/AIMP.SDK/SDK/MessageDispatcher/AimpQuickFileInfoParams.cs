using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.MessageDispatcher;

public struct AimpQuickFileInfoParams
{
    public int Size { get; set; }

    public QfiCommandShow Animation { get; set; }

    public int AnimationTime { get; set; }

    public int DisplayTime { get; set; }

    public byte Opacity { get; set; }

    public IAimpFileInfo FileInfo { get; set; }
}