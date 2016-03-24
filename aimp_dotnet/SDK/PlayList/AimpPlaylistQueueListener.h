#pragma once
#include "..\..\IUnknownInterfaceImpl.h"

namespace AIMP
{
    namespace SDK
    {
        typedef boost::signals::connection ConnectionCallback;
        typedef boost::signal<void(void)> VoidSignal;
        typedef boost::signal<void(void)>::slot_function_type VoidSignalCB;

        using namespace AIMP::SDK;
        using namespace AIMP::SDK::PlayList;

        class AimpPlaylistQueueListener :
            public IUnknownInterfaceImpl<IAIMPPlaylistQueueListener>
        {
        private:
            VoidSignal _contentChanged;
            VoidSignal _stateChanged;

        public:
            typedef IUnknownInterfaceImpl<IAIMPPlaylistQueueListener> Base;

            ConnectionCallback RegisterContentChangedCallback(VoidSignalCB subscriber)
            {
                return _contentChanged.connect(subscriber);
            }

            ConnectionCallback RegisterStateChangedCallback(VoidSignalCB subscriber)
            {
                return _stateChanged.connect(subscriber);
            }

            void UnregisterContentChangedCallback(ConnectionCallback *callback)
            {
                _contentChanged.disconnect(callback);
            }

            void UnregisterStateChangedCallback(ConnectionCallback *callback)
            {
                _stateChanged.disconnect(callback);
            }

            virtual void WINAPI ContentChanged()
            {
                _contentChanged();
            }

            virtual void WINAPI StateChanged()
            {
                _stateChanged();
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

