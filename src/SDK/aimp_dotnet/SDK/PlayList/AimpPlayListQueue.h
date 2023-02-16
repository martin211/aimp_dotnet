//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpPlayListItem.h"
#include "AimpPlayList.h"
#include "AimpPlaylistQueueListener.h"
#include "IPlayListQueueEventExecutor.h"
#include <gcroot.h>

namespace AIMP {
    namespace SDK {
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::Playlist;

        public ref class AimpPlaylistQueue :
            public AimpObject<IAIMPPlaylistQueue>,
            public IAimpPlaylistQueue,
            public IPlayListQueueEventExecutor {
        public:
            explicit AimpPlaylistQueue(IAIMPPlaylistQueue* queue, IAIMPPlaylistQueue2* queue2);

            virtual property bool IsSuspended
            {
                bool get();
                void set(bool value);
            }

            virtual ActionResult Add(IAimpPlaylistItem^ item, bool insertAtBeginning);

            virtual ActionResult AddList(System::Collections::Generic::IList<IAimpPlaylistItem^>^ items,
                                         bool insertAtBeginning);

            virtual int GetItemCount();

            virtual ActionResult Delete(IAimpPlaylist^ playList);

            virtual ActionResult Delete(IAimpPlaylistItem^ item);

            virtual ActionResult Move(IAimpPlaylistItem^ item, int index);

            virtual ActionResult Move(int index, int targetIndex);

            virtual AimpActionResult<IAimpPlaylistItem^>^ GetItem(int index);

            virtual event AimpPlaylistQueueListenerHandler^ ContentChanged
            {
                void add(AimpPlaylistQueueListenerHandler^ onEvent);
                void remove(AimpPlaylistQueueListenerHandler^ onEvent);
                void raise(IAimpPlaylistQueue^ sender);
            }

            virtual event AimpPlaylistQueueListenerHandler^ StateChanged
            {
                void add(AimpPlaylistQueueListenerHandler^ onEvent);
                void remove(AimpPlaylistQueueListenerHandler^ onEvent);
                void raise(IAimpPlaylistQueue^ sender);
            }

            void OnContentChanged() override {
                ContentChanged(this);
            }

            void OnStateChanged() override {
                StateChanged(this);
            }

        private:
            //IAIMPPlaylistQueue* _service = nullptr;
            //IAIMPPropertyList* _properties = nullptr;
            //IAIMPPlaylistQueue2* _queue2 = nullptr;
            AimpPlaylistQueueListenerHandler^ _contentChanged;
            AimpPlaylistQueueListenerHandler^ _stateChanged;
            AimpPlaylistQueueListener* _listner = nullptr;
        protected:
            //IAIMPPlaylistQueue* GetAimpService() override;
        };
    }
}
