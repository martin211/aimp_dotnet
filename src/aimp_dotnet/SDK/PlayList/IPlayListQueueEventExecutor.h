#pragma once

public interface class IPlayListQueueEventExecutor
{
    void OnContentChanged();

    void OnStateChanged();
};