/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

public interface class IPlayListQueueEventExecutor
{
    void OnContentChanged();

    void OnStateChanged();
};
