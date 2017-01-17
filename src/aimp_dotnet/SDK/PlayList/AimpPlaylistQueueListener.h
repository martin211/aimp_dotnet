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

            AimpPlaylistQueueListener(gcroot<IPlayListQueueEventExecutor^> executor)
            {
                _executor = executor;
            }

            virtual void WINAPI ContentChanged()
            {
                _executor->OnContentChanged();
            }

            virtual void WINAPI StateChanged()
            {
                _executor->OnStateChanged();
            }

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
            {
                if (riid == IID_IAIMPPlaylistQueueListener)
                {
                    *ppvObject = this;
                    AddRef();
                    return S_OK;
                }

                ppvObject = NULL;
                return E_NOTIMPL;
            }

            virtual ULONG WINAPI AddRef(void)
            {
                return Base::AddRef();
            }

            virtual ULONG WINAPI Release(void)
            {
                return Base::Release();
            }
        };
    }
}

