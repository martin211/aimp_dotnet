// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "SDK/AimpPropertyList.h"

namespace AIMP
{
    namespace SDK
    {
        public class InternalAimpPlaylistPreimage :
            public IUnknownInterfaceImpl<IAIMPPlaylistPreimage>,
            public IAIMPPlaylistPreimageDataProvider,
            public AimpPropertyList
        {
        private:
            gcroot<Playlist::IAimpPlaylistPreimage^> _managedInstance;

        public:
            typedef IUnknownInterfaceImpl<IAIMPPlaylistPreimage> Base;

            InternalAimpPlaylistPreimage(gcroot<Playlist::IAimpPlaylistPreimage^> managedInstance);

            virtual void WINAPI Finalize();
            virtual void WINAPI Initialize(IAIMPPlaylistPreimageListener* Listener);
            virtual HRESULT WINAPI ConfigLoad(IAIMPStream* Stream);
            virtual HRESULT WINAPI ConfigSave(IAIMPStream* Stream);
            virtual HRESULT WINAPI ExecuteDialog(HWND OwnerWndHanle);
            virtual ULONG WINAPI AddRef(void);
            virtual ULONG WINAPI Release(void);
            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
            virtual HRESULT WINAPI GetFiles(IAIMPTaskOwner* Owner, DWORD** Flags, IAIMPObjectList** List);

            // Read
            HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value) override;
            HRESULT WINAPI GetValueAsObject(int PropertyID, REFIID IID, void** Value) override;
        };
    }
}
