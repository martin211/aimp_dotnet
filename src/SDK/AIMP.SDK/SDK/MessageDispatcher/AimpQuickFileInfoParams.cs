//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.MessageDispatcher;

public enum QfiCommandShow
{
    Hide = 0,
    Show = 1
}

public enum QfiAnimationType
{
    None = 0,
    Fade = 1
}

public struct AimpQuickFileInfoParams
{
    public int Size { get; set; }

    public QfiCommandShow Animation { get; set; }

    public int AnimationTime { get; set; }

    public int DisplayTime { get; set; }

    public byte Opacity { get; set; }

    public IAimpFileInfo FileInfo { get; set; }
}