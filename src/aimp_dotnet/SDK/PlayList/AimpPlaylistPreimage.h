// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "AimpPlaylistPreimageListener.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlaylistPreimage :
            public AimpObject<IAIMPPlaylistPreimage>,
            public IAimpPlaylistPreimage
        {
        public:
            explicit AimpPlaylistPreimage(IAIMPPlaylistPreimage* aimpObject);

            virtual property String^ FactoryId
            {
                String^ get();
            }

            virtual property bool AutoSync
            {
                bool get();
                void set(bool value);
            }

            virtual property bool AutoSyncOnStartup
            {
                bool get();
                void set(bool value);
            }

            virtual property bool HasDialog
            {
                bool get();
                void set(bool value);
            }

            virtual property String^ SortTemplate
            {
                String^ get();
            }

            virtual ActionResultType ConfigLoad(IAimpStream^ stream);

            virtual ActionResultType ConfigSave(IAimpStream^ stream);

            virtual ActionResultType ExecuteDialog(IntPtr ownerHandle);

            virtual void Initialize(IAimpPlaylistPreimageListener^ listener);

            virtual void FinalizeObject();
        };
    }
}
