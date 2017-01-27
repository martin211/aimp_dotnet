/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
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

