/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once
#include "..\..\IUnknownInterfaceImpl.h"
#include "IPlayListQueueEventExecutor.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        class AimpPlaylistQueueListener :
            public IUnknownInterfaceImpl<IAIMPPlaylistQueueListener>
        {
        private:
            gcroot<IPlayListQueueEventExecutor^> _executor;

        public:
            typedef IUnknownInterfaceImpl<IAIMPPlaylistQueueListener> Base;

            AimpPlaylistQueueListener(gcroot<IPlayListQueueEventExecutor^> executor);

            virtual void WINAPI ContentChanged();

            virtual void WINAPI StateChanged();

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

            virtual ULONG WINAPI AddRef(void);

            virtual ULONG WINAPI Release(void);
        };
    }
}

