// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AimpSdk.h"

using namespace Actions;
using namespace Actions::Objects;

namespace AIMP {
    namespace SDK {
        public delegate void AimpActionEventDelegate(gcroot<IAimpActionEvent^> sender, IUnknown* data);

        typedef void (__stdcall *AimpActionEventCallback)(gcroot<IAimpActionEvent^> sender,
                                                          IUnknown* data);
    }
}

class AimpActionEvent : public IUnknownInterfaceImpl<IAIMPActionEvent> {
public:
    typedef IUnknownInterfaceImpl<IAIMPActionEvent> Base;

    /// <summary>
    /// Initializes a new instance of the <see cref="AimpActionEvent"/> class.
    /// </summary>
    /// <param name="managedInstance">The managed instance. Will be returned as a sender to main context.</param>
    /// <param name="executeCallback">The execute callback.</param>
    AimpActionEvent(gcroot<IAimpActionEvent^> managedInstance, AimpActionEventCallback callback);

    virtual void WINAPI OnExecute(IUnknown* Data);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
private:
    gcroot<IAimpActionEvent^> _managedInstance;
    AimpActionEventCallback _cb;
};
