// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "InternalAimpPlaylistPreimage.h"

namespace AIMP {
    namespace SDK {
        using namespace Playlist::Objects;

        public class InternalAimpMLPlaylistPreimage :
            public IUnknownInterfaceImpl<IAIMPMLPlaylistPreimage>,
            public IAIMPPlaylistPreimageDataProvider {
        private:
            gcroot<IAimpPlaylistPreimage^> _managedInstance;
        public:
            typedef IUnknownInterfaceImpl<IAIMPMLPlaylistPreimage> Base;

            InternalAimpMLPlaylistPreimage(gcroot<IAimpPlaylistPreimage^> managedInstance);

            virtual HRESULT WINAPI GetFilter(IAIMPMLDataFilter** Filter);
            virtual HRESULT WINAPI GetStorage(IUnknown** Storage);

            virtual HRESULT WINAPI ExecuteDialog(HWND OwnerWndHanle);
            virtual HRESULT WINAPI GetFiles(IAIMPTaskOwner* Owner, DWORD** Flags, IAIMPObjectList** List);

            virtual void WINAPI Finalize();
            virtual void WINAPI Initialize(IAIMPPlaylistPreimageListener* Listener);
            virtual HRESULT WINAPI ConfigLoad(IAIMPStream* Stream);
            virtual HRESULT WINAPI ConfigSave(IAIMPStream* Stream);

            virtual void WINAPI BeginUpdate();
            virtual void WINAPI EndUpdate();
            virtual HRESULT WINAPI Reset();

            // Read
            virtual HRESULT WINAPI GetValueAsFloat(int PropertyID, double* Value);
            virtual HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value);
            virtual HRESULT WINAPI GetValueAsInt64(int PropertyID, INT64* Value);
            virtual HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void** Value);
            // Write
            virtual HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value);
            virtual HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value);
            virtual HRESULT WINAPI SetValueAsInt64(int PropertyID, const INT64 Value);
            virtual HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown* Value);

            virtual ULONG WINAPI AddRef(void);
            virtual ULONG WINAPI Release(void);
            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
        };
    }
}
